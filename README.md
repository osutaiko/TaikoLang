# TaikoLang
An Esoteric Programming Language Using "Taiko" maps, Based on Brainfuck.

## Language Design
TaikoLang consists of eight commands, listed below. Code written in TaikoLang can be perfectly interchangeable with a Brainfuck script. Each command is 3 notes long, regardless of timing and spacing. All sliders and spinners are omitted.

### Storage
- A single array of 32,768 cells, each having a boundary of [0, 255]. This boundary is equivalent to the `unsigned char` type in C/C++.
- A data pointer, having a soft boundary of [0, 32767]. However, the value of the data pointer is commonly stored as an `int` type.

### Commands
| Command | Conventional Taiko Notation | Brainfuck Equivalent | Function |
| ------- | --------------------------- | -------------------- | -------- |
| 🔴🔴🔴 | `ddd` | `>` | Increment the data pointer (to point to the next cell to the right). |
| 🔴🔴🔵 | `ddk` | `<` | Decrement the data pointer (to point to the next cell to the left). |
| 🔴🔵🔴 | `dkd` | `+` | Increment (increase by one) the byte at the data pointer. |
| 🔴🔵🔵 | `dkk` | `-` | Decrement (decrease by one) the byte at the data pointer. |
| 🔵🔴🔴 | `kdd` | `.` | Output the byte at the data pointer. |
| 🔵🔴🔵 | `kdk` | `,` | Accept one byte of input, storing its value in the byte at the data pointer. |
| 🔵🔵🔴 | `kkd` | `[` | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching `]` command. |
| 🔵🔵🔵 | `kkk` | `]` | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching `[` command. |

### Note
- All array cells and the data pointer value wraps around upon incrementation or decrementation.
- For the text-based expression of TaikoLang, `d`, `k`, `D`, `K` is the only valid characters. Other characters including whitespaces, parentheses, and numbers will be omitted.
- If the total note count is not divisible by 3, the final notes will be omitted as they would not be able to construct a valid 3-note command.

## Examples
### Hello, World!
#### Code
This code is spaced for readability.
```
dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd kkd ddd dkd dkd dkd dkd dkd dkd dkd ddd
dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd ddd dkd dkd dkd ddd dkd ddk ddk ddk ddk
dkk kkk ddd dkd dkd kdd ddd dkd kdd dkd dkd dkd dkd dkd dkd dkd kdd kdd dkd dkd
dkd kdd ddd dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd dkd kdd dkk dkk
dkk dkk dkk dkk dkk dkk dkk dkk dkk dkk kdd ddk ddk dkd dkd dkd dkd dkd dkd dkd
dkd dkd dkd dkd dkd dkd dkd dkd kdd ddd kdd dkd dkd dkd kdd dkk dkk dkk dkk dkk
dkk kdd dkk dkk dkk dkk dkk dkk dkk dkk kdd ddd dkd kdd
```

The full code in the form of an osu!taiko map can be viewed [here](https://twitter.com/ye_osu/status/1487819314124103681?s=20&t=W3yS92ToHIEd26ftLNKEiQ) in my Tweet.

#### Output
`Hello, World!`

#### Brainfuck Equivalent
The TaikoLang code is equivalent to the following Brainfuck script:
```
++++++++++
[>+++++++>++++++++++>+++>+<<<<-]
>++.
>+.
+++++++..
+++.
>++++++++++++++.
------------.
<<+++++++++++++++.
>.
+++.
------.
--------.
>+.
```
