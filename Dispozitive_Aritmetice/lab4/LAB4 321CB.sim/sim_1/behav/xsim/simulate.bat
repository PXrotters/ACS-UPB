@echo off
REM ****************************************************************************
REM Vivado (TM) v2022.1 (64-bit)
REM
REM Filename    : simulate.bat
REM Simulator   : Xilinx Vivado Simulator
REM Description : Script for simulating the design by launching the simulator
REM
REM Generated by Vivado on Thu Mar 28 14:53:05 +0200 2024
REM SW Build 3526262 on Mon Apr 18 15:48:16 MDT 2022
REM
REM IP Build 3524634 on Mon Apr 18 20:55:01 MDT 2022
REM
REM usage: simulate.bat
REM
REM ****************************************************************************
REM simulate design
echo "xsim ViataEoSimulare_behav -key {Behavioral:sim_1:Functional:ViataEoSimulare} -tclbatch ViataEoSimulare.tcl -protoinst "protoinst_files/Sumator16Biti.protoinst" -log simulate.log"
call xsim  ViataEoSimulare_behav -key {Behavioral:sim_1:Functional:ViataEoSimulare} -tclbatch ViataEoSimulare.tcl -protoinst "protoinst_files/Sumator16Biti.protoinst" -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
