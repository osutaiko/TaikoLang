# TaikoLang
TaikoLang is a Brainf*ck-based esoteric programming language using Taiko no Tatsujin (太鼓の達人) maps.


## Language Design
TaikoLang consists of eight commands, listed below. Scripts written in TaikoLang is interchangeable with equivalent BF scripts. Each command is 3 notes long, regardless of timing and spacing. All sliders and spinners will be omitted.

### Storage
- A single array of 32,768 cells, each having a boundary of [0, 255]. This boundary is equivalent to the `unsigned char` type in C/C++.
- A data pointer, having a soft boundary of [0, 32767]. However, the value of the data pointer is commonly stored as an `int` type, and will be dealed as such in this implementation.

### Commands
| Command | Conventional Taiko Notation | Brainf*ck Equivalent | Function |
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
- For the text-based expression of TaikoLang, `d`, `k`, `D`, `K` are the only valid characters. Other characters including whitespaces, parentheses, and numbers will be ignored.
- If the total note count is not a multiple of 3, the final notes will be omitted as they would not be able to construct a valid 3-note command.


## Implementation
Currently this project only takes `.osu` type files (osu! beatmap file format) in taiko mode, for the _true taiko programming expericence_. You may compile any of the following files for the desired conversion. You should use the map editor of the [osu! game client](https://osu.ppy.sh/home/download) (stable) as an IDE for TaikoLang.
| File Name | Input | Output |
| --------- | ----- | ------ |
| `bf_to_tl_converter.cpp` | BF code as text | TaikoLang code in conventional text notation |
| `taikolang_osu.cpp` | `.osu` file of the TaikoLang script (prompted input as file path) | Execution of the script |
| `taikolang_text.cpp` | TaikoLang script as text-based expressions | Execution of the script |


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

The gameplay video of the full code in the form of an osu!taiko map can be viewed in my ~~tweet (deleted)~~. You may also _play_ the map in the osu! game client itself.
- The original osu! map is __[Anamanaguchi - STILL SPLODIN' THO (Interlude)](https://osu.ppy.sh/beatmapsets/104151#taiko/274500)__ mapped by [Liiraye](https://osu.ppy.sh/users/1280641).

#### Output
`Hello, World!`

#### In BF
The TaikoLang code is equivalent to the following BF script:
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
