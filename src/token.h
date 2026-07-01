#pragma once
#include <string>

enum class TokenKind {

  // Key words
  Let,
  Function,
  Requires,
  Scene,
  If,
  Else,
  Loop,
  Break,
  Return,
  Match,

  // Types
  Coins,
  Chance,
  Reputation,

  // Builtins
  Say,
  Ask,
  Roll,
  Flip,
  Draw,
  Gain,
  Lose,
  Enter,

  // Arithmetic ops
  Plus,
  Minus,
  Star,
  Slash,

  // Compare ops
  Eq,
  EqEq,
  Neq,
  Lt,
  Gt,
  Leq,
  Geq,


  // Symbols
  LParen,
  RParen,
  Colon,
  Arrow,
  Dollar,
  Comma,
  Newline,

  // Lits
  IntLit,
  StringLit,
  

  // Others
  Ident,
  Eof,
};

struct Token {
  TokenKind kind;
  std::string value;
  int line;
  int col;
};
