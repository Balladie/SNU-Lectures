--------------------------------------------------------------------------------
-- TiTle       : Clock Divider
--------------------------------------------------------------------------------
-- Date        : 2004/02/02
-- Author      : Hyunjoong Lee(ithabise@gmail.com)
-- Revision    : 1.1
--------------------------------------------------------------------------------
-- Description : This block divides FPGA board's original 50MHz clock.
--               Output clock's duration is 5 second.
--               For Traffic Light Control in Logic Circuit @ SNU EECS
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MAKE_CLK is
     Port ( MCLK      : in std_logic;
            RESET_IN  : in std_logic;
            CLOCK     : out std_logic;
            RESET_OUT : out std_logic);
end MAKE_CLK;

architecture Behavioral of MAKE_CLK is

     signal counter : std_logic_vector(26 downto 0) := "000000000000000000000000000";
     signal clkdiv  : std_logic := '0';

begin

     -- count up
     process(MCLK, RESET_IN)
         begin
              -- reset counter when reset is high
              if(RESET_IN = '1') then
                   counter <= "000000000000000000000000000";
                   clkdiv <= '0';
              -- otherwise start counting
              elsif(MCLK = '1' and MCLK'EVENT) then
                   -- check counter value
                   if(counter = "111011100110101100101000000") then
                        -- reset counter
                        counter <= "000000000000000000000000000";
                        -- invert divided output clock
                        clkdiv <= not clkdiv;
                   else
                        -- count up
                        counter <= counter + 1;
                   end if;
              end if;
     end process;

     -- relay reset and clock
     RESET_OUT <= RESET_IN;
     CLOCK <= clkdiv;

end Behavioral;
