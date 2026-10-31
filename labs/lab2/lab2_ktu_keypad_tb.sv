// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 10/27/2026
// Test bench for top module tb 
// "automatic testbench which demonstrates all four output transitions, enable and reset features"
// "automatic testbench"

`timescale 1 ns/1 ps
module lab2_ktu_tb ();
		logic [3:0] switchLeft; // the four DIP switches (on the board, SW6)
		logic [3:0] switchRight; // the off board DIP switch
		logic [3:0] column; // columns into FPGA
		logic reset; // switch for reset on the board
		logic enable; // switch for enable on the board
		logic clk; //create a clock signal
		logic [2:0] led;   // 3 LEDs (you may use the on-board LEDs)
		logic [6:0] seg;   // the segments of a common-anode 7-segment display
		logic leftHex; // to toggle the left seven segment power
		logic rightHex; // to toggle the right seven segment power
		logic [3:0] keyLead;  // to toggle the LEDs
		logic [1:0] rowNum;  // R0 - 00, R1 - 01, R2 - 10, or R3 - 11
	
	// Instantiate the lab1_ktu DUT for testing 
    lab2_ktu lab2_ktu(
        .switchLeft(switchLeft),
        .switchRight(switchRight),
        .column(column),
				.reset(reset),
				.enable(enable),
        .led(led),
				.seg(seg),
				.leftHex(leftHex),
				.rightHex(rightHex),
				.keyLead(keyLead)
    );
	
	// generates the clock to oscillate
	always 
		begin
			clk = 1; #5; clk = 0; #5;
		end
	
	initial begin

        //  ========== TESTING TOP MODULE OF KEYPAD =========
		// REFER TO LAB 1 for testing feature of the seven segment and the led logic tests
			// testing all 16 input to outputs for the keyLead = ~columns
			  column = 4'b0000;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1111)       // check outputs
            $display("(1) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(1) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);

			  column = 4'b0001;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1110)       // check outputs
            $display("(2) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(2) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b0010;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1101)       // check outputs
            $display("(3) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(3) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b0011;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1100)       // check outputs
            $display("(4) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(4) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b0100;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1011)       // check outputs
            $display("(5) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(5) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);

			  column = 4'b0101;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1010)       // check outputs
            $display("(6) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(6) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b0110;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1001)       // check outputs
            $display("(7) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(7) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b0111;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b1000)       // check outputs
            $display("(8) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(8) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1000;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0111)       // check outputs
            $display("(9) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(9) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);

			  column = 4'b1001;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0110)       // check outputs
            $display("(10) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(10) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1010;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0101)       // check outputs
            $display("(11) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(11) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1011;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0100)       // check outputs
            $display("(12) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(12) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1100;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0011)       // check outputs
            $display("(13) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(13) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);

			  column = 4'b1101;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0010)       // check outputs
            $display("(14) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(14) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1110;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0001)       // check outputs
            $display("(15) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(15) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
			  column = 4'b1111;            // setup inputs
        #10;                        // wait required time
        assert (keyLead == 4'b0000)       // check outputs
            $display("(16) PASSED! keyLead is correctly the flipped bits of column as desired at time: %0t.", $time);
        else 
            $error("(16) FAILED! keyLead behaves based on column incorrectly at time: %0t.", $time);
	

	
	    #100 $finish;
	end	
endmodule
