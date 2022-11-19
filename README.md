# PI4IOE5V9536

This is an Arduino library/driver for the Diodes Inc.  [PI4IOE5V9536](https://www.diodes.com/part/view/PI4IOE5V9536/), a 4-bit general-purpose I/O expander that provides remote I/O expansion for most microcontroller families via the I2C-bus interface.

This library is derived from hideakitai's [PCA95x5](https://github.com/hideakitai/PCA95x5) library.

See the output.ino example sketch for usage. input.ino **has not been ported yet**.

This driver **has not been tested yet** (no hardware).

## Status

|    Date    | Status                                                    |
| :--------: | --------------------------------------------------------- |
| 2022-11-19 | **Untested**. Boards and parts have not been ordered yet. |

## Source Changes

Changes to source repo:

* Changes due to being a 4-channel device with a reduced feature set.
* Replaced namespaces with an IOX_ prefix.
* Removed the TwoWire abstraction.
* Overloaded begin() with options to expedite output LOW. Returns status.
* Changed the I2C address (**UNVERIFIED**).

## License

MIT
