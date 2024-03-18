//// To use Compressonator Framework "C" interfaces, just include
//// a single header file and CMP_Framework lib into  your projects
//
//#include "compressonator.h"
//
// //--------------------------
// // Init frameworks
// // plugin and IO interfaces
// //--------------------------
//CMP_InitFramework();
//
////---------------
//// Load the image
////---------------
//CMP_MipSet MipSetIn;
//memset(&MipSetIn, 0, sizeof(CMP_MipSet));
//cmp_status = CMP_LoadTexture(pszSourceFile, &MipSetIn);
//if (cmp_status != CMP_OK) {
//    std::printf("Error %d: Loading source file!\n", cmp_status);
//    return -1;
//}
//
////----------------------------------------------------------------------
//// generate mipmap level for the source image, if not already generated
////----------------------------------------------------------------------
//
//if (MipSetIn.m_nMipLevels <= 1)
//{
//    CMP_INT requestLevel = 10; // Request 10 miplevels for the source image
//
//    //------------------------------------------------------------------------
//    // Checks what the minimum image size will be for the requested mip levels
//    // if the request is too large, a adjusted minimum size will be returned
//    //------------------------------------------------------------------------
//    CMP_INT nMinSize = CMP_CalcMinMipSize(MipSetIn.m_nHeight, MipSetIn.m_nWidth, 10);
//
//    //--------------------------------------------------------------
//    // now that the minimum size is known, generate the miplevels
//    // users can set any requested minumum size to use. The correct
//    // miplevels will be set acordingly.
//    //--------------------------------------------------------------
//    CMP_GenerateMIPLevels(&MipSetIn, nMinSize);
//}
//
////==========================
//// Set Compression Options
////==========================
//KernelOptions   kernel_options;
//memset(&kernel_options, 0, sizeof(KernelOptions));
//
//kernel_options.format = destFormat;   // Set the format to process
//kernel_options.fquality = fQuality;     // Set the quality of the result
//kernel_options.threads = 0;            // Auto setting
//
////=====================================================
//// example of using BC1 encoder options 
//// kernel_options.bc15 is valid for BC1 to BC5 formats
////=====================================================
//if (destFormat == CMP_FORMAT_BC1)
//{
//    // Enable punch through alpha setting
//    kernel_options.bc15.useAlphaThreshold = true;
//    kernel_options.bc15.alphaThreshold = 128;
//
//    // Enable setting channel weights
//    kernel_options.bc15.useChannelWeights = true;
//    kernel_options.bc15.channelWeights[0] = 0.3086f;
//    kernel_options.bc15.channelWeights[1] = 0.6094f;
//    kernel_options.bc15.channelWeights[2] = 0.0820f;
//}
//
////--------------------------------------------------------------
//// Setup a results buffer for the processed file,
//// the content will be set after the source texture is processed
//// in the call to CMP_ProcessTexture()
////--------------------------------------------------------------
//CMP_MipSet MipSetCmp;
//memset(&MipSetCmp, 0, sizeof(CMP_MipSet));
//
////===============================================
//// Compress the texture using Framework Lib
////===============================================
//cmp_status = CMP_ProcessTexture(&MipSetIn, &MipSetCmp, kernel_options, CompressionCallback);
//if (cmp_status != CMP_OK) {
//    ...
//}
//
////----------------------------------------------------------------
//// Save the result into a DDS file
////----------------------------------------------------------------
//cmp_status = CMP_SaveTexture(pszDestFile, &MipSetCmp);
//
//CMP_FreeMipSet(&MipSetIn);
//CMP_FreeMipSet(&MipSetCmp);