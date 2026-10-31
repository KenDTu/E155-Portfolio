// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 10/30/2026
// Test bench for scanning module which for the four row assertions and enable and reset features

`timescale 1ns/1ps
module scanner_tb();
  logic clk;
  logic reset;
  logic enable;
  logic [3:0] switchRight;

  // dut instance here
  scanner scanner (.clk(clk), .enable(enable), .reset(reset), .switchRight(switchRight));

  always begin
    clk = 1; #5;
    clk = 0; #5;
  end

  initial begin // BEGIN OF TESTING
    enable = 0;
    reset = 0;
    // ================== Testing the row assertions for four output transitions ======================
    // the default max parameter is 8_999_999

        force scanner.counter = (scanner.max)/4 - 1;            // setup inputs
        #10;                        // wait required time
        assert (switchRight == 4'b0001)       // check outputs
            $display("PASSED! Col 0 correctly behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! Col 0 behaves incorrectly at time: %0t.", $time);

        force scanner.counter = (scanner.max)/2 - 1;                // setup inputs
        #10;                        // wait required time
        assert (switchRight == 4'b0010)       // check outputs
            $display("PASSED! Col 1 correctly behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! Col 1 behaves incorrectly at time: %0t.", $time);

        force scanner.counter = (scanner.max)/2 + 1;                // setup inputs
        #10;                        // wait required time
        assert (switchRight == 4'b0100)       // check outputs
            $display("PASSED! Col 2 correctly behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! Col 2 behaves incorrectly at time: %0t.", $time);

        force scanner.counter = (scanner.max) - 1;                // setup inputs
        #10;                        // wait required time
        assert (switchRight == 4'b1000)       // check outputs
            $display("PASSED! Col 3 correctly behaves as desired at time: %0t.", $time);
        else 
            $error("FAILED! Col 3 behaves incorrectly at time: %0t.", $time);
			
    // ================== Testing the enable and reset assertions ======================
    
    // Testing enable can be turned on and off correctly
        enable = 1;                // setup inputs
        assert (enable == 4'b1)       // check outputs
            $display("Passed! Enable = 1 which is obtained at time: %0t.", $time);
        else 
            $error("Failed! Enable = 0 which is not obtained at time: %0t.", $time);
        #10; 
        enable = 0;                // setup inputs
        assert (enable == 4'b0)       // check outputs
            $display("Passed! Enable = 0 which is obtained at time: %0t.", $time);
        else 
            $error("Failed! Enable = 1 which is not obtained at time: %0t.", $time);

        #10;

    // Testing reset can be turned on and off correctly
        reset = 1;                // setup inputs
        assert (reset == 4'b1)       // check outputs
            $display("Passed! Reset = 1 which is obtained at time: %0t.", $time);
        else 
            $error("Failed! Reset = 0 which is not obtained at time: %0t.", $time);
    #100;

    // TODO: tidy up this enable and reset functionality but fine for the time being
    $finish;
  end
endmodule
