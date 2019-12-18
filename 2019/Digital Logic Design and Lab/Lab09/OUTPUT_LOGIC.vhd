library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity OUTPUT_LOGIC is
     Port ( MCLK    : in std_logic;
            CLOCK   : in std_logic;
            HGREEN  : in std_logic;
            HLEFT   : in std_logic;
            HYELLOW : in std_logic;
            HRED    : in std_logic;
            FLEFT   : in std_logic;
            FYELLOW : in std_logic;
            FRED    : in std_logic;
            FS      : in std_logic;
            HS      : in std_logic;
            LED     : out std_logic_vector(7 downto 0);
            ANODE   : out std_logic_vector(3 downto 0);
            SEG     : out std_logic_vector(7 downto 0));
end OUTPUT_LOGIC;

architecture Behavioral of OUTPUT_LOGIC is

     -- divided for 7SEGs driving
     signal clkdiv  : std_logic_vector(15 downto 0) := "0000000000000000";
     -- counter for 7SEGs driving
     signal counter : std_logic_vector(1 downto 0) := "00";
     -- 7SEGS letters
     signal SEG3    : std_logic_vector(7 downto 0) := "11111111";
     signal SEG2    : std_logic_vector(7 downto 0) := "11111111";
     signal SEG1    : std_logic_vector(7 downto 0) := "11111111";
     signal SEG0    : std_logic_vector(7 downto 0) := "11111111";
     -- Letter assignment for waiting car state
     constant HCAR  : std_logic_vector(7 downto 0) := "10010001"; -- H
     constant FCAR  : std_logic_vector(7 downto 0) := "01110001"; -- F
     constant NOCAR : std_logic_vector(7 downto 0) := "11111111"; -- no display

begin

     -- CLOCK and Traffic Light assignment to LEDs
     LED(7) <= CLOCK;
     LED(6) <= HRED;
     LED(5) <= HYELLOW;
     LED(4) <= HLEFT;
     LED(3) <= HGREEN;
     LED(2) <= FRED;
     LED(1) <= FYELLOW;
     LED(0) <= FLEFT;

     -- 7SEGMENT displaying
     SEG3 <= "11111111"; -- no display
     SEG2 <= "11111111"; -- no display
     SEG1 <= HCAR when HS = '1' else NOCAR;
     SEG0 <= FCAR when FS = '1' else NOCAR;

     -- anode selection
     process(MCLK)
          begin
               if(MCLK = '1' and MCLK'EVENT) then
                    clkdiv <= clkdiv + 1;
               end if;
     end process;
     counter(1) <= clkdiv(15);
     counter(0) <= clkdiv(14);
     ANODE(3 downto 0) <= "1110" when counter = "00" else
                          "1101" when counter = "01" else
                          "1101" when counter = "10" else
                          "1101" when counter = "11";
     SEG <= SEG0 when counter = "00" else
            SEG1 when counter = "01" else
            SEG2 when counter = "10" else
            SEG3 when counter = "11";

end Behavioral;


