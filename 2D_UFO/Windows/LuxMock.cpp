//
// LuxMock.cpp
//

#include "pch.h"
#include "LuxMock.h"

#define HGR_WIDTH  140
#define HGR_HEIGHT 192
#define SCREEN_TEX_PITCH ((256 * 8 * 4 + 7) / 8)

unsigned int HB[192]= {
    0x2000, 0x2400, 0x2800, 0x2C00, 0x3000, 0x3400, 0x3800, 0x3C00,
    0x2080, 0x2480, 0x2880, 0x2C80, 0x3080, 0x3480, 0x3880, 0x3C80,
    0x2100, 0x2500, 0x2900, 0x2D00, 0x3100, 0x3500, 0x3900, 0x3D00,
    0x2180, 0x2580, 0x2980, 0x2D80, 0x3180, 0x3580, 0x3980, 0x3D80,
    0x2200, 0x2600, 0x2A00, 0x2E00, 0x3200, 0x3600, 0x3A00, 0x3E00,
    0x2280, 0x2680, 0x2A80, 0x2E80, 0x3280, 0x3680, 0x3A80, 0x3E80,
    0x2300, 0x2700, 0x2B00, 0x2F00, 0x3300, 0x3700, 0x3B00, 0x3F00,
    0x2380, 0x2780, 0x2B80, 0x2F80, 0x3380, 0x3780, 0x3B80, 0x3F80,
    0x2028, 0x2428, 0x2828, 0x2C28, 0x3028, 0x3428, 0x3828, 0x3C28,
    0x20A8, 0x24A8, 0x28A8, 0x2CA8, 0x30A8, 0x34A8, 0x38A8, 0x3CA8,
    0x2128, 0x2528, 0x2928, 0x2D28, 0x3128, 0x3528, 0x3928, 0x3D28,
    0x21A8, 0x25A8, 0x29A8, 0x2DA8, 0x31A8, 0x35A8, 0x39A8, 0x3DA8,
    0x2228, 0x2628, 0x2A28, 0x2E28, 0x3228, 0x3628, 0x3A28, 0x3E28,
    0x22A8, 0x26A8, 0x2AA8, 0x2EA8, 0x32A8, 0x36A8, 0x3AA8, 0x3EA8,
    0x2328, 0x2728, 0x2B28, 0x2F28, 0x3328, 0x3728, 0x3B28, 0x3F28,
    0x23A8, 0x27A8, 0x2BA8, 0x2FA8, 0x33A8, 0x37A8, 0x3BA8, 0x3FA8,
    0x2050, 0x2450, 0x2850, 0x2C50, 0x3050, 0x3450, 0x3850, 0x3C50,
    0x20D0, 0x24D0, 0x28D0, 0x2CD0, 0x30D0, 0x34D0, 0x38D0, 0x3CD0,
    0x2150, 0x2550, 0x2950, 0x2D50, 0x3150, 0x3550, 0x3950, 0x3D50,
    0x21D0, 0x25D0, 0x29D0, 0x2DD0, 0x31D0, 0x35D0, 0x39D0, 0x3DD0,
    0x2250, 0x2650, 0x2A50, 0x2E50, 0x3250, 0x3650, 0x3A50, 0x3E50,
    0x22D0, 0x26D0, 0x2AD0, 0x2ED0, 0x32D0, 0x36D0, 0x3AD0, 0x3ED0,
    0x2350, 0x2750, 0x2B50, 0x2F50, 0x3350, 0x3750, 0x3B50, 0x3F50,
    0x23D0, 0x27D0, 0x2BD0, 0x2FD0, 0x33D0, 0x37D0, 0x3BD0, 0x3FD0
};

unsigned char dhrbytes[16][4] = {
    0x00,0x00,0x00,0x00,
    0x08,0x11,0x22,0x44,
    0x11,0x22,0x44,0x08,
    0x19,0x33,0x66,0x4C,
    0x22,0x44,0x08,0x11,
    0x2A,0x55,0x2A,0x55,
    0x33,0x66,0x4C,0x19,
    0x3B,0x77,0x6E,0x5D,
    0x44,0x08,0x11,0x22,
    0x4C,0x19,0x33,0x66,
    0x55,0x2A,0x55,0x2A,
    0x5D,0x3B,0x77,0x6E,
    0x66,0x4C,0x19,0x33,
    0x6E,0x5D,0x3B,0x77,
    0x77,0x6E,0x5D,0x3B,
    0x7F,0x7F,0x7F,0x7F
};

byte rgb[16][3] = {
    {  0,   0,   0},    //"black",     // 0
    {243,   0,  64},    //"magenta",   // 8
    { 64,  20, 255},    //"darkBlue",  // 1
    {255,   0, 255},    //"purple",    // 9
    {  0, 155,  64},    //"darkGreen", // 2
    {128, 128, 128},    //"gray",      //10
    {  0, 175, 255},    //"blue",      // 3
    {191, 147, 255},    //"lightBlue", //11
    { 64, 108,   0},    //"brown",     // 4
    {255,  80,   0},    //"orange",    //12
    {128, 128, 128},    //"grey",      // 5
    {255, 100, 191},    //"pink",      //13
    {  0, 255,   0},    //"green",     // 6
    {191, 235,   0},    //"yellow",    //14
    { 12, 255, 191},    //"aqua",      // 7
    {255, 255, 255}     //"white"      //15
};

byte videoMemory[0x4000] = {};

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

extern "C" {
    typedef void (*PreVBlank)();
    extern byte *memoryMain;
    extern byte *memoryAux;
    extern void (*System_PrintDebug)(char* lineBuffer);
    extern bool mainStart();
    extern bool mainStep(PreVBlank preVBlank);
    extern void mainStop();
}

void Game_PrintDebug(char* lineBuffer)
{
    static wchar_t debugStringBuffer[1024];
    mbstowcs_s(nullptr, debugStringBuffer, 1024, lineBuffer, _TRUNCATE);
    OutputDebugString(debugStringBuffer);
    OutputDebugString(L"\n");
}

void Game_PreVBlank() {
    memcpy(videoMemory, memoryMain+0x2000, 0x2000);
    memcpy(videoMemory+0x2000, memoryAux+0x2000, 0x2000);
}

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    mainStop();
    free(memoryMain);
    free(memoryAux);

    if (m_deviceResources)
    {
        m_deviceResources->WaitForGpu();
    }
}

// Initialize the Direct3D resources required to run.
bool Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    // game start
    System_PrintDebug = Game_PrintDebug;
    return mainStart();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

    // game step
    if (!mainStep(Game_PreVBlank))
        PostQuitMessage(0);

    PIXEndEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // Prepare the command list to render a new frame.
    m_deviceResources->Prepare();

    auto device = m_deviceResources->GetD3DDevice();

    // Clear back buffers
    ResourceUploadBatch resourceUpload(device);
    resourceUpload.Begin();
    Clear();
    auto uploadResourcesFinished = resourceUpload.End(
        m_deviceResources->GetCommandQueue());
    uploadResourcesFinished.wait();

    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Render");

    // TODO: Add your rendering code here.
    ID3D12DescriptorHeap* heaps[] = { m_resourceDescriptors->Heap(), m_states->Heap() };
    commandList->SetDescriptorHeaps(static_cast<UINT>(std::size(heaps)), heaps);

    // Updated background
    for (int y=0; y<HGR_HEIGHT; y++) {
        for (int x=0; x<HGR_WIDTH; x++) {
            byte p = GetPixel(x, y);
            if (p<16) {
                m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+0] = rgb[p][0];
                m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+1] = rgb[p][1];
                m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+2] = rgb[p][2];
            }
        }
    }
    resourceUpload.Begin();
    DX::ThrowIfFailed(
        CreateDDSTextureFromMemory(device, resourceUpload, m_ddsLuxScreen, sizeof(m_ddsLuxScreen), m_background.ReleaseAndGetAddressOf(), true));
    CreateShaderResourceView(device, m_background.Get(),
                             m_resourceDescriptors->GetCpuHandle(Descriptors::Background));
    uploadResourcesFinished = resourceUpload.End(
        m_deviceResources->GetCommandQueue());
    uploadResourcesFinished.wait();

#if 1
    m_spriteBatch->Begin(commandList);

    m_spriteBatch->Draw(m_resourceDescriptors->GetGpuHandle(Descriptors::Background),
        GetTextureSize(m_background.Get()),
        m_fullscreenRect);

    m_spriteBatch->End();
#endif

    PIXEndEvent(commandList);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();

    // DirectX Tool Kit for DX12
    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    PIXEndEvent();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    auto commandList = m_deviceResources->GetCommandList();
    PIXBeginEvent(commandList, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto const rtvDescriptor = m_deviceResources->GetRenderTargetView();
    auto const dsvDescriptor = m_deviceResources->GetDepthStencilView();

    commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
    commandList->ClearRenderTargetView(rtvDescriptor, Colors::CornflowerBlue, 0, nullptr);
    commandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // Set the viewport and scissor rect.
    auto const viewport = m_deviceResources->GetScreenViewport();
    auto const scissorRect = m_deviceResources->GetScissorRect();
    commandList->RSSetViewports(1, &viewport);
    commandList->RSSetScissorRects(1, &scissorRect);

    PIXEndEvent(commandList);
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // Check Shader Model 6 support
    D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = { D3D_SHADER_MODEL_6_0 };
    if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel)))
        || (shaderModel.HighestShaderModel < D3D_SHADER_MODEL_6_0))
    {
#ifdef _DEBUG
        OutputDebugStringA("ERROR: Shader Model 6.0 is not supported!\n");
#endif
        throw std::runtime_error("Shader Model 6.0 is not supported!");
    }

    // DirectX Tool Kit for DX12
    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    // TODO: Initialize device dependent objects here (independent of window size).
    m_states = std::make_unique<CommonStates>(device);

    m_resourceDescriptors = std::make_unique<DescriptorHeap>(device,
        Descriptors::Count);

    ResourceUploadBatch resourceUpload(device);

    resourceUpload.Begin();

    // Init background
    *((DWORD *)m_ddsLuxScreen) = DDS_MAGIC;
    DDS_HEADER *header = (DDS_HEADER *)(m_ddsLuxScreen+sizeof(DWORD));

    memset(header, 0, sizeof(DDS_HEADER));
    header->size              = sizeof(DDS_HEADER);
    header->flags             = DDS_HEADER_FLAGS_TEXTURE | DDS_HEADER_FLAGS_PITCH | DDS_HEADER_FLAGS_MIPMAP;
    header->height            = 256;
    header->width             = 256;
    header->pitchOrLinearSize = SCREEN_TEX_PITCH;
    header->mipMapCount       = 1;
    header->ddspf             = DDSPF_A8B8G8R8;
    header->caps              = DDS_SURFACE_FLAGS_TEXTURE;

    byte *tex = m_ddsLuxScreen+DDS_PREFIX;
    for (int y=0; y<256; y++) {
        for (int x=0; x<256; x++) {
            tex[y*SCREEN_TEX_PITCH+x*4+0] = 64;
            tex[y*SCREEN_TEX_PITCH+x*4+1] = 64;
            tex[y*SCREEN_TEX_PITCH+x*4+2] = 64;
            tex[y*SCREEN_TEX_PITCH+x*4+3] = 255;
        }
    }

    m_ddsLuxAppleScreen = tex+((256-HGR_HEIGHT)/2)*SCREEN_TEX_PITCH+((256-HGR_WIDTH)/2)*4;
    for (int y=0; y<HGR_HEIGHT; y++) {
        for (int x=0; x<HGR_WIDTH; x++) {
            m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+0] = 0;
            m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+1] = 0;
            m_ddsLuxAppleScreen[y*SCREEN_TEX_PITCH+x*4+2] = 0;
        }
    }

    DX::ThrowIfFailed(
        CreateDDSTextureFromMemory(device, resourceUpload, m_ddsLuxScreen, sizeof(m_ddsLuxScreen), m_background.ReleaseAndGetAddressOf(), true));

    CreateShaderResourceView(device, m_background.Get(),
        m_resourceDescriptors->GetCpuHandle(Descriptors::Background));

    RenderTargetState rtState(m_deviceResources->GetBackBufferFormat(),
        m_deviceResources->GetDepthBufferFormat());

#if 0
    SpriteBatchPipelineStateDescription pd(rtState);
#endif

#if 0
    SpriteBatchPipelineStateDescription pd(rtState,
        &CommonStates::NonPremultiplied);
#endif

#if 1
    auto sampler = m_states->LinearWrap();
    SpriteBatchPipelineStateDescription pd(rtState,
        nullptr, nullptr, nullptr, &sampler);
#endif

    m_spriteBatch = std::make_unique<SpriteBatch>(device, resourceUpload, pd);

    auto uploadResourcesFinished = resourceUpload.End(
        m_deviceResources->GetCommandQueue());

    uploadResourcesFinished.wait();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    auto viewport = m_deviceResources->GetScreenViewport();
    m_spriteBatch->SetViewport(viewport);

    auto size = m_deviceResources->GetOutputSize();
    m_screenPos.x = float(size.right) / 2.f;
    m_screenPos.y = float(size.bottom) / 2.f;

    m_fullscreenRect = m_deviceResources->GetOutputSize();

    m_stretchRect.left = size.right / 4;
    m_stretchRect.top = size.bottom / 4;
    m_stretchRect.right = m_stretchRect.left + size.right / 2;
    m_stretchRect.bottom = m_stretchRect.top + size.bottom / 2;
}

byte Game::GetPixel(byte x, byte y) {
    int xoff, pattern, idx;
    unsigned char *ptraux, *ptrmain, c1, c2, d1, d2;

    pattern = (x%7);
    xoff = HB[y] + ((x/7) * 2);
    ptraux  = videoMemory+xoff;
    ptrmain  = videoMemory+xoff-0x2000;

    /* left this here for reference

    unsigned char dhrpattern[7][4] = {
    0,0,0,0,
    0,0,0,1,
    1,1,1,1,
    1,1,2,2,
    2,2,2,2,
    2,3,3,3,
    3,3,3,3};
    */

    /* compare colors in the input file to color patterns and return drawcolor */
    /* somewhat inelegant but lazy to read and debug if a problem */
    switch (pattern) {
    case 0:
        c1 = ptraux[0] &0x0f;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][0] & 0x0f;
            if (d1 == c1) return idx;
        }
        break;
    case 1:
        c1 = ptraux[0] & 0x70;
        c2 = ptrmain[0] & 0x01;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][0] & 0x70;
            d2 = dhrbytes[idx][1] & 0x01;
            if (d1 == c1 && d2 == c2) return idx;
        }
        break;
    case 2:
        c1 = ptrmain[0] & 0x1e;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][1] & 0x1e;
            if (d1 == c1) return idx;
        }
        break;
    case 3:
        c1 = ptrmain[0] & 0x60;
        c2 = ptraux[1] & 0x03;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][1] & 0x60;
            d2 = dhrbytes[idx][2] & 0x03;
            if (d1 == c1 && d2 == c2) return idx;
        }
        break;
    case 4:
        c1 = ptraux[1] & 0x3c;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][2] & 0x3c;
            if (d1 == c1) return idx;
        }
        break;
    case 5:
        c1 = ptraux[1] & 0x40;
        c2 = ptrmain[1] & 0x07;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][2] & 0x40;
            d2 = dhrbytes[idx][3] & 0x07;
            if (d1 == c1 && d2 == c2) return idx;
        }
        break;
    case 6:
        c1 = ptrmain[1] & 0x78;
        for (idx = 0; idx < 16; idx++) {
            d1 = dhrbytes[idx][3] & 0x78;
            if (d1 == c1) return idx;
        }
        break;
    }

    return 255;
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_spriteBatch.reset();
    m_background.Reset();
    m_resourceDescriptors.reset();
    m_states.reset();

    // DirectX Tool Kit for DX12
    m_graphicsMemory.reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
