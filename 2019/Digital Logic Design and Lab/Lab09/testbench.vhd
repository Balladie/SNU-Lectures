--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:25:09 01/16/2013
-- Design Name:   
-- Module Name:   C:/Users/bhs9822/test_string/testb.vhd
-- Project Name:  test_string
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: str
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
--TYPE std_logic_vector_vector IS ARRAY (natural RANGE <>) OF std_logic_vector;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY testb IS
END testb;
 
ARCHITECTURE behavior OF testb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT tlc_top
    PORT(
         MCLK : IN  std_logic;
         RESET : IN  std_logic;
         HS : IN  std_logic;
         FS : IN  std_logic;
		 LED : OUT std_logic_vector(7 DOWNTO 0);
		 ANODE : OUT std_logic_vector(3 DOWNTO 0);
		 SEG : OUT std_logic_vector(7 DOWNTO 0)
        );
    END COMPONENT;
    

   --Inputs
   signal MCLK : std_logic := '0';
   signal RESET : std_logic := '0';
   signal HS : std_logic := '0';
   signal FS : std_logic := '0';

 	--Outputs
   signal LED : std_logic_vector(7 DOWNTO 0);
   signal ANODE : std_logic_vector(3 DOWNTO 0);
   signal SEG : std_logic_vector(7 DOWNTO 0);

   -- Clock period definitions
   constant CLOCK_period : time := 20 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: tlc_top PORT MAP (
          MCLK => MCLK,
          RESET => RESET,
          HS => HS,
          FS => FS,
		  LED => LED,
		  ANODE => ANODE,
		  SEG => SEG
			 --STAT => STAT
        );

   -- Clock process definitions
   CLOCK_process :process
   begin
		MCLK <= '0';
		wait for CLOCK_period/2;
		MCLK <= '1';
		wait for CLOCK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
		RESET <= '1';
			wait for 10 us;
		RESET <= '0';
			wait for 8 us;
		HS <= '1';
			wait for 5 us;
		HS <= '0';
			wait for 12.5 us;
		FS <= '1';
			wait for 2.5 us;
		FS <= '0';
			wait for 7.5 us;
		HS <= '1';
			wait for 2.5 us;
		HS <= '0';
			wait for 15 us;
      -- insert stimulus here 

      wait;
   end process;

END;
