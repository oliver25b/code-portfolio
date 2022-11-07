-- Arithmetic Logic Unit (16 functions)
-- Tyler Miller
-- Partners: Oliver Bartz, Christian Meintel
-- Project04 Part 1
-- October 19, 2022

library IEEE;
use     IEEE.std_logic_1164.all;
use     IEEE.numeric_std.all;

-------------
entity ALU is
------------- 
    generic ( BITS   : natural := 8 );                             -- ALU bit width
    port    ( RESET  : in std_logic;                               -- Active high master reset
              CLOCK  : in std_logic;                               -- Master clock
              ENABLE : in std_logic;                               -- Clock enable
              OPCODE : in std_logic_vector         ( 3 downto 0);  -- ALU operation
              DIN    : in std_logic_vector  ( BITS - 1 downto 0);  -- Data input
              ACCUM  : out std_logic_vector ( BITS - 1 downto 0);  -- Accumulator output
              FLAGS  : out std_logic_vector        ( 3 downto 0)); -- Status flags output (NVCZ)
    end ALU;
	
--------------------------
architecture RTL of ALU is
--------------------------
    
	type   OPERATION_BIN is array ( natural range <>) of unsigned ( BITS downto 0); 
  signal OPERATIONS  :  OPERATION_BIN       ( 0  to  15);                         -- ALU operations results array
	signal A, B        :  unsigned   ( BITS - 1  downto 0);                         -- Registers for A and B for inputs
	signal AIN, BIN    :  unsigned   ( BITS      downto 0);                         -- Internal register for A and B
	signal N, V, C, Z  :  std_logic;                                                -- flags
	signal ZERO        :  std_logic;                                                -- to check for zero flag
	signal OVERFLOW    :  std_logic;                                                -- to check for overflow
  signal CARRY       :  natural range 0 to 1;                                     -- to check for Carry
	signal INSTRUCTION :  natural range 0 to 15;                                    -- to select which instruction is wanted
	signal RESULT      :  unsigned   ( BITS      downto 0);                         -- ALU operations result 
	
begin

    INSTRUCTION <= To_Integer   ( unsigned ( OPCODE));                            -- Converting OPCODE to a natural

            AIN <= resize       ( A, BITS + 1);                                   -- shift A register
            BIN <= resize       ( B, BITS + 1) when ( INSTRUCTION = 0) else       -- When ADD operation resize B array
				           To_Unsigned  ( 1, BITS + 1) when ( INSTRUCTION = 2) else       -- INC
				           (others => '1')             when ( INSTRUCTION = 3) else       -- DEC
				           resize       (not B, BITS + 1) ;                               -- SUB and CMP
				   
	        CARRY <= 1 when ( INSTRUCTION < 2 and C = '1') else                     -- CMP
		               1 when ( INSTRUCTION = 4) else                                 -- ADD and SUB
		               0;                                                             
				   
		   RESULT <= OPERATIONS ( INSTRUCTION);                                                                -- Selection of ALU result based on the output of OPCODE

	   OVERFLOW	<=     RESULT ( BITS - 1) when ( AIN ( BITS - 1) = '0' and BIN ( BITS - 1) = '0') else       -- Flag calculations 
                 not RESULT ( BITS - 1) when ( AIN ( BITS - 1) = '1' and BIN ( BITS - 1) = '1') else '0';  -- 
				   
         ZERO <= '1' when ( RESULT ( BITS	- 1 downto 0) = 0) else '0';                                     -- Flag Calculations
		   
	   

     
	OPERATIONS  ( 0)  <= AIN + BIN + CARRY;                               -- ADD operation
	OPERATIONS  ( 1)  <= AIN + BIN + CARRY;                               -- SUB operation
	OPERATIONS  ( 2)  <= AIN + BIN + CARRY;                               -- INC operation
	OPERATIONS  ( 3)  <= AIN + BIN + CARRY;                               -- DEC operation
	OPERATIONS  ( 4)  <= AIN + BIN + CARRY;                               -- CMP operation
	OPERATIONS  ( 5)  <= A     & C;                                       -- SLL operation
	OPERATIONS  ( 6)  <= A (0) & C             & A ( BITS - 1 downto 1);  -- SRR operation
	OPERATIONS  ( 7)  <= A (0) & A ( BITS - 1) & A ( BITS - 1 downto 1);  -- ASR operation
	OPERATIONS  ( 8)  <= '0'   & ( A or  B);                              -- OR  operation
	OPERATIONS  ( 9)  <= '0'   & ( A and B);                              -- AND operation
	OPERATIONS  ( 10) <= '0'   & ( A xor B);                              -- XOR operation
	OPERATIONS  ( 11) <= '0'   &     not A;                               -- NOT operation
	OPERATIONS  ( 12) <= '0'   & unsigned ( DIN);                         -- LDA operation
	OPERATIONS  ( 13) <= '0'   & unsigned ( DIN);                         -- LDB operation
	OPERATIONS  ( 14) <= '0'   & unsigned ( DIN);                         -- CLC operation
	OPERATIONS  ( 15) <= '1'   & unsigned ( DIN);                         -- SEC operation
	
	
----------------------------------------------
REGISTER_PROCESS: process (RESET, CLOCK) begin
----------------------------------------------
    if ( RESET = '1') then                                              -- When Reset is 1
          A <= ( others => '0');                                        -- Set all bits of A to 0
          B <= ( others => '0');                                        -- Set all bits of B to 0
    elsif ( CLOCK'event and CLOCK = '1') then                           -- if clock event happens or clock is 1
       if ( ENABLE = '1') then                                          -- if Enable is 1 and a clock event happened or clock is 1 then
          case INSTRUCTION is
            when 0 to 3  => A <= RESULT ( BITS-1 downto 0);             -- Takes care of ADD, SUB, INC, DEC operations
		
            when 5 to 12 => A <= RESULT ( BITS-1 downto 0);             -- Takes care of SLL, SRR, ASR, OR, AND, XOR, NOT, LDA operations
		
            when 13      => B <= RESULT ( BITS-1 downto 0);             -- Takes care of LDB operations
		
            when others  => null;                                       -- When CMP, CLC, SEC is selected drive to null
         end case;
       end if;
    end if;
  end process;
 
 
------------------------------------------
FLAG_PROCESS: process (RESET, CLOCK) begin
------------------------------------------
  if ( RESET = '1') then                                           -- If RESET is 1 then set all Flags to 0
          N <= '0';                                                
          V <= '0';                                                
          C <= '0';                                                 
          Z <= '0';                                                
  elsif ( CLOCK'event and CLOCK = '1') then                        -- If CLOCK event happens or CLOCK is 1
     if ( ENABLE = '1') then                                       -- If ENABLE is one then 
      case INSTRUCTION is                                          
         when  0 to 1  => N <= RESULT ( BITS - 1);                 -- When ADD or SUB then flags change N gets result of BITS - 1
                          V <= OVERFLOW;                           -- V flag gets OVERFLOW data
				                  C <= RESULT ( BITS);                     -- C flag gets result of BITS call
				                  Z <= ZERO;                               -- Z flag gets Zero data
					 
	       when  2 to 7  => N <= RESULT ( BITS - 1);                 -- When INC, DEC, CMP, SLL, SRR, ASR operations are called
	                        C <= RESULT ( BITS);                     -- 
					                Z <= ZERO;                               -- 
	  
	       when  8 to 13 => N <= RESULT ( BITS - 1);                 -- When OR, AND, XOR, NOT, LDA, LDB operations are called
	                        Z <= ZERO;                               -- 
	  
	       when 14 to 15 => C <= RESULT ( BITS);                     -- When CLC, SEC operations are called
      end case;
     end if;
  end if;  
end process;


ACCUM <= std_logic_vector (A);                                     -- OUTPUT DRIVER
FLAGS <= N & V & C & Z;                                            -- OUTPUT DRIVER

end architecture;

