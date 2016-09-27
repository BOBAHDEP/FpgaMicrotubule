#pragma once
#include "rc47-api.h"

#include <vector>
#include <iostream>

#define HLS_LENGTH 0x154
#define HLS_A 0x160
#define HLS_B 0x164
#define HLS_OFFSET_I 0x158
#define HLS_OFFSET_O 0x15C
#define HLS_CP_SIZE 0x168


#define SEED_REG 0x170

// #define SIZE_DWORD    (((4*N_d*13)+32)/32)

// // #define SIZE_DWORD  0x80*(int)(((4*N_d*13) / (float)0x80+1)) 
// #define SIZE_BYTE    4*SIZE_DWORD   

#define coeffs_ddr_offset 8096


#define MAX_BOARDS   (MAX_RC47_BOARDS)
#define MAX_DEVS     (MAX_RC47_BOARDS * 5)


#define SIZE_DWORD  0x80*(int)(((2*36*13)/(float)0x80+1))
#define SIZE_BYTE   8*SIZE_DWORD

namespace microtubule {

  typedef struct {
    float d0;
    float d1; 
  } two_floats;   


  class FpgaDev {

  public:

    FpgaDev();
    int FindDevices(void);
    int open(int board, int chip_select);
    int close(int dev);

    int StartRandomGenerator(int dev, int L, unsigned int *seeds);
    int StopRandomGenerator(int dev);    

    int LoadCoeffs(int dev, int NumCoeffs, float *coeffs);

    int CalcDynamics(  int                  dev,
                       unsigned int         n_step,           //time steps to run 
                       unsigned int         n_layers,        // number of layers to calculate. should be a multiple of 12
                
                       std::vector<std::vector<float> > &x,
                       std::vector<std::vector<float> > &y,
                       std::vector<std::vector<float> > &t,
                       std::vector<std::vector<int> > &type
                     ) ; 

  private: 

    int GetIndexByDev(int dev);

    struct rc47_board_t rc47[MAX_BOARDS];

    struct pci_device pd[MAX_DEVS];
    

    // unsigned int   *wr_buf[MAX_DEVS], *wr_buf_free[MAX_DEVS];
    // unsigned int   *rd_buf[MAX_DEVS], *rd_buf_free[MAX_DEVS];      
    unsigned int   *wr_buf, *wr_buf_free;
    unsigned int   *rd_buf, *rd_buf_free;    

    int num_boards = -1; 

    int devs[MAX_DEVS]; 


  };

} // namespace microtubule

