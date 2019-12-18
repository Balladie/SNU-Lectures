--------------------------------------------------------------------------------
-- TiTle       : Data Register
--------------------------------------------------------------------------------
-- Date        : 2005/12/21
-- Author      : Hyunjoong Lee(ithabise@gmail.com)
-- Revision    : 1.1
--------------------------------------------------------------------------------
-- Description : This block senses turning-left traffic signal.
--               It is held until turning-left light is high.
--               For Traffic Light Control in Logic Circuit @ SNU EECS
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DATA_REG is
     Port ( MCLK   : in std_logic;
            FS_IN  : in std_logic;
            HS_IN  : in std_logic;
            FLEFT  : in std_logic;
            HLEFT  : in std_logic;
            FS_OUT : out std_logic;
            HS_OUT : out std_logic);
end DATA_REG;

architecture Behavioral of DATA_REG is

	
     -- FS/HS internal signal
     signal fs_internal : std_logic := '0';
     signal hs_internal : std_logic := '0';
     signal fs_catch : std_logic := '0';
     signal hs_catch : std_logic := '0';

begin

     process(MCLK)
          begin
               if(MCLK='1' and MCLK'EVENT) then
                    fs_catch <= fs_internal;
                    hs_catch <= hs_internal;
               else
                    fs_catch <= fs_catch;
                    hs_catch <= hs_catch;
               end if;
     end process;
     process(FS_IN, FLEFT, fs_catch)
          begin
               -- (S=0/R=0) HOLD
               if(FS_IN = '0' and FLEFT = '0') then
                    fs_internal <= fs_catch;
               -- (S=1/R=0) SET
               elsif(FS_IN = '1' and FLEFT ='0') then
                    fs_internal <= '1';
               -- (S=0/R=1) RESET
               elsif(FS_IN = '0' and FLEFT = '1') then
                    fs_internal <= '0';
               else
                    fs_internal <= '0';
               end if;
     end process;
     process(HS_IN, HLEFT, hs_catch)
          begin
               -- (S=0/R=0) HOLD
               if(HS_IN = '0' and HLEFT = '0') then
                    hs_internal <= hs_catch;
               -- (S=1/R=0) SET
               elsif(HS_IN = '1' and HLEFT ='0') then
                    hs_internal <= '1';
               -- (S=0/R=1) RESET
               elsif(HS_IN = '0' and HLEFT = '1') then
                    hs_internal <= '0';
               else
                    hs_internal <= '0';
               end if;
     end process;

     -- signal output
     FS_OUT <= fs_catch;
     HS_OUT <= hs_catch;

end Behavioral;