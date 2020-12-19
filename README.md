# hamming_distance_intelTBB
In this project, I have implemented an algorithm to compute the minimum hamming distance of 32 bits integers. First you need to make sure you have cloned this repository:

    git clone https://github.com/miladebrahimipour/hamming_distance_intelTBB.git
    cd hamming_distance_intelTBB

Then create a build folder and navigate to it:
    
    mkdir build
    cd build

Then you can build and run the algorithm seperately using CMake:
    
    cmake ..
    make
    ./HammingDistance

This will build the a binary that computes the minimum hamming distance of an array that was randomly generated. The binary contains two algorithms, one is a serial computation of Hamming Distance, and the other is a parallel version which is implemented using Intel TBB.
The number of tests (array elements) is controlled by test macro defined as 'SIZE_OF_ARRAY'. 

Please note that in order to run the binary code successfully, you need to instal Intel TBB library.
