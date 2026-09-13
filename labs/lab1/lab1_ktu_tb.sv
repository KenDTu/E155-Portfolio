// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 09/0/2026
// Test bench for top module tb 
// “are the connections to submodules correct?”, 
// “does the HSOSC work?” 
// and “does the assign 1 liner work?”.

`timescale 1 ns/1 ps
module lab1_ktu_tb();
	logic clk, reset; // system clock, active high reset
	logic [3:0] s; // input switches
	logic [2:0] led; // output from logic
	logic [6:0] seg; // output the segments of a common-anode 7-segment display
	
	// Instantiate the lab1_ktu DUT for testing
    lab1_ktu lab1_ktu(
        .s(s),
        .reset(reset),
		.led(led),
        .seg(seg)
    );
	
	// generates the clock to oscillate
	always 
		begin
			clk = 1; #5; clk = 0; #5;
		end
	
	initial begin
		
	//  ========== TESTING TOP LEVEL LOGIC ==========
	// test xor 1
        s[1] = 1'b0; s[0] = 1'b0;    			 // setup inputs
        #10;                        // wait required time
        assert (led[0] == 1'b0)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
	// test xor 2
        s[1] = 1'b0; s[0] = 1'b1;                // setup inputs
        #10;                        // wait required time
        assert (led[0] == 1'b1)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time);
			
	// test xor 3
        s[1] = 1'b1; s[0] = 1'b0;                // setup inputs
        #10;                        // wait required time
        assert (led[0] == 1'b1)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

	// test xor 4
        s[1] = 1'b1; s[0] = 1'b1;                // setup inputs
        #10;                        // wait required time
        assert (led[0] == 1'b0)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
	

	// test and 1
        s[3] = 1'b0; s[2] = 1'b0;                // setup inputs
        #10;                        // wait required time
        assert (led[1] == 1'b0)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
	// test and 2
        s[3] = 1'b0; s[2] = 1'b1;                // setup inputs
        #10;                        // wait required time
        assert (led[1] == 1'b0)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
	// test and 3
        s[3] = 1'b1; s[2] = 1'b0;                // setup inputs
        #10;                        // wait required time
        assert (led[1] == 1'b0)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
	// test and 4
        s[3] = 1'b1; s[2] = 1'b1;                // setup inputs
        #10;                        // wait required time
        assert (led[1] == 1'b1)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time);
			
	// check clock is 1 or 0 to see it works
	// ============ TESTING CONNECTIONS TO SUBMODULES ==================== 
	

	
	// ============ TESTING FUNCTIONALITY OF HSOSC =======================
	
    // ============ TESTING FUNCTIONALITY OF SEVEN SEGMENT =======================
    // example test 0
        s = 4'b0000;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b100_0000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
            
    // test 1
        s = 4'b0001;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b111_1001)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

    // test 2
        s = 4'b0010;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b010_0100)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test 3
        s = 4'b0011;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b011_0000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test 4
        s = 4'b0100;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b001_1001)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

    // test 5
        s = 4'b0101;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b001_0010)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test 6
        s = 4'b0110;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_0010)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test 7
        s = 4'b0111;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b111_1000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

    // test 8
        s = 4'b1000;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_0000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test 9
        s = 4'b1001;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b001_1000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test A
        s = 4'b1010;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_1000)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

    // test B
        s = 4'b1011;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_0011)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test C
        s = 4'b1100;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b100_0110)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test D
        s = 4'b1101;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b010_0001)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

    // test E
        s = 4'b1110;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_0110)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 
			
    // test F
        s = 4'b1111;                // setup inputs
        #10;                        // wait required time
        assert (seg == 7'b000_1110)       // check outputs
            $display("PASSED! The led controller behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! The led controller behaves incorrectly at time: %0t.", $time); 

			
	//  ========== TESTING TOP LEVEL LOGIC ==========
	
	
	    #100 $stop;
	end	
endmodule