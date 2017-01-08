# peggo: A PEG Parser Generator

[![Build Status](https://travis-ci.org/Baltoli/peggo.svg?branch=master)](https://travis-ci.org/Baltoli/peggo)

This project aims to implement a PEG parser generator. It is a future project
for me, and as such this repository is mostly ideas for now until I have some
more time to spend on it.

## Design

* Should take in a textual representation of a PEG grammar and output compiled
  code + header that together implement a parser for that grammar.
* How should the output format be specified? Raw parse tree output vs. working
  out an API that users can use to hook into the parsing process.

Problem: we want to be able to hook into the parsing process somehow. The
natural way to do this is to register functions to particular non-terminals in
the grammar. These functions will get given the full text parsed by that
non-terminal, and can return a `void *`.

    Digit <- 0 | 1 ... 9
    Number <- +Digit

So then to extract a number from a parse using this grammar:

    struct number_parse {
      unsigned long value;
    };

    void *num_cb(char *string, void **parses) {
      struct number_parse *p = malloc(...);
      unsigned long v = strtol(string);
      p->value = v;
      return (void *)p;
    }

    register_callback("Number", &num_cb);

The parser would then automatically call into this function on a successful
parse of a Number non-terminal. But we also need to be able to handle the case
where a non-terminal needs to be able to access its subcomponents - in this
case, the callbacks could also take a number of results (positional?)

Key - have start be a non-terminal and only call the callback once? So that the
AST builder can be separated from the parsing logic.

So we have a 'whole parse' callback that is given an array of sub-parses (start,
end index) to work with.

So the parser constructs a parse tree - nodes in the tree are productions of the
grammar together with the start and end index into the string for that
particular production. e.g.

    Start [0,3]
      Number [0,3]
        Digit [0,1]
        Digit [1,1]
        Digit [2,1]

Every node in the parse tree therefore will have an identical structure:

    typedef struct peg_parse_st {
      char *symbol;
      size_t start;
      size_t length;
      peg_parse_t *children;
      size_t n_children;
    } peg_parse_t;

Then an AST can be constructed from the parse tree by recursively walking it
rather than using a callback mechanism.

What qualifies as a child in the parse tree data structure? Sequences and zero /
one or more are what we need to be able to represent, but can't really at the
moment.

Consider
    
    Number <- Digit+
    Digit <- 0 | 1

The grammar in this situation is

    Number:
      OneOrMore(
        NonTerminal(
          'Digit'
        )
      )

    Digit:
      Choice(
        Terminal('0')
        Terminal('1)
      )

Ideally we'd like to represent this (in the parse tree) as something like:

    Number 0:3
      Digit 0:1
        0:1 '0'
      Digit 1:1
        1:1 '1'
      Digit 2:1
        2:1 '0'

So what I think this means is that *sequential* operators in the grammar
(sequence, zero-or-more and one-or-more) need to be added in a *flat* way to
their parent. Only non-terminals can have children in the tree (from production
rules).

One way to do this is to pass a pointer to the parent into the parsing
functions. This would restore the recursive nature of parsing while still
allowing for many children to share the same parent node. When a non-terminal is
reached in the parser, we would look up the corresponding rule in the grammar.
Then, run each sub-component of the parsing expression with the parent passed
in. Finally, once the recursion is done, the parent can compute its own length
from its children's lengths.
