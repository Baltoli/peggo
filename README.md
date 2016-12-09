# peggo: A PEG Parser Generator

This project aims to implement a PEG parser generator. It is a future project
for me, and as such this repository is mostly ideas for now until I have some
more time to spend on it.

## Design

* Should take in a textual representation of a PEG grammar and output compiled
  code + header that together implement a parser for that grammar.
* How should the output format be specified? Raw parse tree output vs. working
  out an API that users can use to hook into the parsing process.
