/* -------------------------------------------------------------------- */
/* Manual for the sample program                                        */
/* -------------------------------------------------------------------- */
The LIN 2.0 slave driver for RL78/F13 and RL78/F14.
                                                    Version 0.07


/* -------------------------------------------------------------------- */
/* History                                                              */
/* -------------------------------------------------------------------- */
2013/03/29 A.Kondo      Ver 0.01 1st creation.
2013/04/08 A.Kondo      Ver 0.02 A few modifications.
2013/08/22 A.Kondo      Ver 0.03 Deviations of RL78/F14 UM(Rev1.00) were reflected.
2015/02/04 S.Sugawara   Ver 0.04 Deviations of RL78/F14 UM(Rev2.00) were reflected.
2015/06/10 S.Sugawara   Ver 0.05 Correction of errors.
2016/02/02 A.Kondo      Ver 0.06 The restriction for fMX was added.
2016/06/14 S.Sugawara   Ver 0.07 CS+ CC-RL support.


/* -------------------------------------------------------------------- */
/* Outline                                                              */
/* -------------------------------------------------------------------- */
This document explains about LIN 2.0 slave driver.


/* -------------------------------------------------------------------- */
/* Folder composition                                                   */
/* -------------------------------------------------------------------- */
Folder composition is shown below.

Root folder
   |
   +-conf                               : The folder for configuration
   |   |
   |   +-conflin.c                      : The configuration file for the LIN 2.0 slave driver
   |   |
   |   +-conflin.h                      : The configuration header file for the LIN 2.0 slave driver
   |
   +-liblin2                            : The folder including files for generating a LIN 2.0 library
   |   |
   |   +-liblin2.mtpj                   : Project file for CS+ CA78K0R
   |   |
   |   +-liblin2_CCRL.mtpj              : Project file for CS+ CC-RL
   |   |
   |   +-iodefine.h                     : I/O registers definition file for CS+ CC-RL
   |   |
   |   +-(Other folder)
   |
   +-libsrc                             : The folder for the driver program
   |   |
   |   +-conf                           : The folder for driver configuration
   |   |   |
   |   |   +-confslin_opt.h             : The driver configuration header file
   |   |   | 
   |   |   +-(Other header files)
   |   |
   |   +-dev                            : Device dependence folder
   |   |
   |   +-(Other files)
   |
   +-readme.txt                         : This file


/* -------------------------------------------------------------------- */
/* Usage                                                                */
/* -------------------------------------------------------------------- */

[How to compile library]

  1. Modify as necessary the driver configuration [libsrc/conf/confslin_opt.h].
  2. Read The following project file at CS+.
        CS+ CA78K0R : liblin2/liblin2.mtpj
        CS+ CC-RL   : liblin2/liblin2_CCRL.mtpj
  3. Select "Build Tool" in the project tree.
     The display of "Build Tool" in each compiler is as follows.
        CS+ CA78K0R : CA78K0R(Build Tool)
        CS+ CC-RL   : CC-RL(Build Tool)
  4. Select "Compile Options" tag, add the compile option "macro definition" if needed.
      (See [A list of compile options], which will be described later)
  5. Select "Build Tool" in the project tree.
     Select "I/O Header File Generation Options" tag,
     Set "Update I/O header file on build" of "I/O Header File" as "Yes(Checking the device file)".
     When the device file has been updated at build, the I/O header file("iodefine.h") is updated.
  6. Select [Build]->[Build Project], it is compiled and linked.
  7. By default, the library file will be created under liblin2.
     If you want to link with application program, copy library file in the application folder.
     The library file name is as follows.
       CS+ CA78K0R F liblin2.lib
       CS+ CC-RL   F liblin2_CCRL.lib

[A list of compile options]

  1. Series of a micro computer
    __LIN_RL78_F13_F14__    : RL78/F13,F14 series

  2. Channel
    __LIN_CH0_P1__          : RLIN3 use of channel 0(Transmission:P13 , Reception:P14)
    __LIN_CH0_P4__          : RLIN3 use of channel 0(Transmission:P42 , Reception:P43)
    __LIN_CH1_P1__          : RLIN3 use of channel 1(Transmission:P10 , Reception:P11)
    __LIN_CH1_P10__         : RLIN3 use of channel 1(Transmission:P106, Reception:P107)

  3. Use hardware auto baudrate detection
    __LIN_HW_AUTO_BR__      : Use auto automatic baud rate

  4. Assembler version of the memory copy routine
    __LIN_MEMCOPY_ASM__

  5. There are 32 extensions defined in the frame signal
    __LIN_SIGNAL_32__

 - 1,2 Select Always.
   Select it even when compiled application.
 - Select 3,4,5 necessary.
   (If you do not select a 3, Describe the baud rate to be used to conflin.c.)
   (4 Small, medium model is not available outside.)
   (5 must match the selection in the presence or absence of both the library and the application.)
 - If you are using a memory copy routine assembler version, you need to pass the 2 and 4 to the assembler.


/* -------------------------------------------------------------------- */
/* Limitations                                                          */
/* -------------------------------------------------------------------- */
 - If driver uses fMX as LIN communication clock, don't use timeout error detection
   and set frequency [fCLK >= fMX x 1.2].
   Compile error will occur when fMX and timeout error detection are selected at
   same time.


/* -------------------------------------------------------------------- */
/* Supplement                                                           */
/* -------------------------------------------------------------------- */
 - After setting the contents of the register LCHSEL channel selection RLIN3, with this driver, 
   but it does not return to its previous value setting.
   Therefore, if you use a different channel in your software, register access is done in the interrupt disabled,
   Set the value to LCHSEL before access.


/* -------------------------------------------------------------------- */
/* Notice                                                               */
/* -------------------------------------------------------------------- */
 - This software is a software for reference purposes only, it is not guaranteed by the Company this behavior.
   If you use this software, 
   thank you to your application so that the product is used on a thorough evaluation on a set of customers.


/* End of files */
