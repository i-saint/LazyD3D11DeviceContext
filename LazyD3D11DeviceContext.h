#ifndef _LazyD3D11DeviceContext_h_
#define _LazyD3D11DeviceContext_h_
#include <D3D11.h>

// D3D11 の DeviceContext は、重複する render state の変更を最適化してくれません。
// 例えば、PSSetShader() などを同じ引数で連続して呼び出した場合もドライバで逐次ステート変更が起こり、
// draw call が非常に多い場合馬鹿にならないコストが発生します。
// 
// この問題を緩和するため、LazyD3D11DeviceContext はステートの変更をバッファリングし、
// Draw*() もしくは Dispatch*() を呼ぶ直前に変更があった部分だけ render state を更新します。
// 
// 使い方は、通常通り ID3D11DeviceContext を作成した後、LazyD3D11DeviceContext::Create() にそれを渡して塗り替えるだけです。
// 開放は Release() が 0 になるタイミングで勝手に行います。
// 
// ex)
// D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
//                                     D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );
// g_pImmediateContext = LazyD3D11DeviceContext::Create(g_pImmediateContext);


class LazyD3D11DeviceContext : public ID3D11DeviceContext
{
typedef ID3D11DeviceContext super;
public:
    struct RenderStates
    {
        ID3D11PixelShader       *PSShader;
        ID3D11VertexShader      *VSShader;
        ID3D11GeometryShader    *GSShader;
        ID3D11HullShader        *HSShader;
        ID3D11DomainShader      *DSShader;
        ID3D11ComputeShader     *CSShader;
        ID3D11ClassInstance     *PSClassInstances[256]; // 定数が見つからないが、ドキュメントには最大 256 とある
        ID3D11ClassInstance     *VSClassInstances[256];
        ID3D11ClassInstance     *GSClassInstances[256];
        ID3D11ClassInstance     *HSClassInstances[256];
        ID3D11ClassInstance     *DSClassInstances[256];
        ID3D11ClassInstance     *CSClassInstances[256];
        UINT                    PSNumClassInstances;
        UINT                    VSNumClassInstances;
        UINT                    GSNumClassInstances;
        UINT                    HSNumClassInstances;
        UINT                    DSNumClassInstances;
        UINT                    CSNumClassInstances;
        ID3D11ShaderResourceView *PSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11ShaderResourceView *VSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11ShaderResourceView *GSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11ShaderResourceView *DSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11ShaderResourceView *HSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11ShaderResourceView *CSShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11Buffer *PSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11Buffer *VSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11Buffer *GSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11Buffer *DSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11Buffer *HSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11Buffer *CSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        ID3D11SamplerState *PSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11SamplerState *VSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11SamplerState *GSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11SamplerState *HSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11SamplerState *DSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11SamplerState *CSSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        ID3D11UnorderedAccessView *CSUnorderedAccesses[D3D11_PS_CS_UAV_REGISTER_COUNT];
        UINT CSUnorderedInitialCounts[D3D11_PS_CS_UAV_REGISTER_COUNT];
        D3D11_PRIMITIVE_TOPOLOGY IAPrimitiveTopology;
        ID3D11InputLayout *IAInputLayout;
        ID3D11Buffer *IAIndexBuffer;
        DXGI_FORMAT IAIndexBufferFormat;
        UINT IAIndexBufferOffset;
        ID3D11Buffer *IAVertexBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        UINT IAVertexBufferStrides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        UINT IAVertexBufferOffsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        ID3D11RenderTargetView *OMRenderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        ID3D11DepthStencilView *OMDepthStencil;
        ID3D11UnorderedAccessView *OMUnorderedAccesses[D3D11_PS_CS_UAV_REGISTER_COUNT];
        UINT OMUnorderedInitialCounts[D3D11_PS_CS_UAV_REGISTER_COUNT];
        ID3D11BlendState *OMBlendState;
        FLOAT OMBlendFactor[4];
        UINT OMBlendSampleMask;
        ID3D11DepthStencilState *OMDepthStencilState;
        UINT OMStencilRef;
        ID3D11Buffer *SOTargets[D3D11_SO_BUFFER_SLOT_COUNT];
        UINT SOOffsets[D3D11_SO_BUFFER_SLOT_COUNT];
        ID3D11RasterizerState *RSRasterState;
        UINT RSNumViewports;
        D3D11_VIEWPORT RSViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
        UINT RSNumScissorRects;
        D3D11_RECT RSScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

        RenderStates();
    };

    struct CallStates
    {
        bool PSSetShader;
        bool VSSetShader;
        bool GSSetShader;
        bool HSSetShader;
        bool DSSetShader;
        bool CSSetShader;
        bool PSSetShaderResources;
        bool VSSetShaderResources;
        bool GSSetShaderResources;
        bool HSSetShaderResources;
        bool DSSetShaderResources;
        bool CSSetShaderResources;
        bool PSSetConstantBuffers;
        bool VSSetConstantBuffers;
        bool GSSetConstantBuffers;
        bool HSSetConstantBuffers;
        bool DSSetConstantBuffers;
        bool CSSetConstantBuffers;
        bool PSSetSamplers;
        bool VSSetSamplers;
        bool GSSetSamplers;
        bool HSSetSamplers;
        bool DSSetSamplers;
        bool CSSetSamplers;
        bool CSSetUnorderedAccessViews;
        bool IASetInputLayout;
        bool IASetVertexBuffers;
        bool IASetIndexBuffer;
        bool IASetPrimitiveTopology;
        bool OMSetRenderTargets;
        bool OMSetRenderTargetsAndUnorderedAccessViews;
        bool OMSetBlendState;
        bool OMSetDepthStencilState;
        bool SOSetTargets;
        bool RSSetState;
        bool RSSetViewports;
        bool RSSetScissorRects;

        CallStates();
        void Clear();
    };

private:
    ID3D11DeviceContext *m_super;
    RenderStates m_rsp;
    RenderStates m_rs;
    CallStates m_cs;

    void AcualSetRenderState();
    void SyncToActualDeviceContext();
    LazyD3D11DeviceContext(ID3D11DeviceContext *_super);

public:
    static ID3D11DeviceContext* Create(ID3D11DeviceContext *_super);



    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        REFIID riid,
        __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

    virtual ULONG STDMETHODCALLTYPE AddRef(void);

    virtual ULONG STDMETHODCALLTYPE Release(void);

    virtual void STDMETHODCALLTYPE GetDevice( 
        ID3D11Device **ppDevice);

    virtual HRESULT STDMETHODCALLTYPE GetPrivateData( 
        REFGUID guid,
        UINT *pDataSize,
        void *pData);

    virtual HRESULT STDMETHODCALLTYPE SetPrivateData( 
        REFGUID guid,
        UINT DataSize,
        const void *pData);

    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface( 
        REFGUID guid,
        const IUnknown *pData);



    virtual void STDMETHODCALLTYPE VSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE PSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE PSSetShader( 
        ID3D11PixelShader *pPixelShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE PSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE VSSetShader( 
        ID3D11VertexShader *pVertexShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE DrawIndexed( 
        UINT IndexCount,
        UINT StartIndexLocation,
        INT BaseVertexLocation);

    virtual void STDMETHODCALLTYPE Draw( 
        UINT VertexCount,
        UINT StartVertexLocation);

    virtual HRESULT STDMETHODCALLTYPE Map( 
        ID3D11Resource *pResource,
        UINT Subresource,
        D3D11_MAP MapType,
        UINT MapFlags,
        D3D11_MAPPED_SUBRESOURCE *pMappedResource);

    virtual void STDMETHODCALLTYPE Unmap( 
        ID3D11Resource *pResource,
        UINT Subresource);

    virtual void STDMETHODCALLTYPE PSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE IASetInputLayout( 
        ID3D11InputLayout *pInputLayout);

    virtual void STDMETHODCALLTYPE IASetVertexBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppVertexBuffers,
        const UINT *pStrides,
        const UINT *pOffsets);

    virtual void STDMETHODCALLTYPE IASetIndexBuffer( 
        ID3D11Buffer *pIndexBuffer,
        DXGI_FORMAT Format,
        UINT Offset);

    virtual void STDMETHODCALLTYPE DrawIndexedInstanced( 
        UINT IndexCountPerInstance,
        UINT InstanceCount,
        UINT StartIndexLocation,
        INT BaseVertexLocation,
        UINT StartInstanceLocation);

    virtual void STDMETHODCALLTYPE DrawInstanced( 
        UINT VertexCountPerInstance,
        UINT InstanceCount,
        UINT StartVertexLocation,
        UINT StartInstanceLocation);

    virtual void STDMETHODCALLTYPE GSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE GSSetShader( 
        ID3D11GeometryShader *pShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE IASetPrimitiveTopology( 
        D3D11_PRIMITIVE_TOPOLOGY Topology);

    virtual void STDMETHODCALLTYPE VSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE VSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE Begin( 
        ID3D11Asynchronous *pAsync);

    virtual void STDMETHODCALLTYPE End( 
        ID3D11Asynchronous *pAsync);

    virtual HRESULT STDMETHODCALLTYPE GetData( 
        ID3D11Asynchronous *pAsync,
        void *pData,
        UINT DataSize,
        UINT GetDataFlags);

    virtual void STDMETHODCALLTYPE SetPredication( 
        ID3D11Predicate *pPredicate,
        BOOL PredicateValue);

    virtual void STDMETHODCALLTYPE GSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE GSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE OMSetRenderTargets( 
        UINT NumViews,
        ID3D11RenderTargetView *const *ppRenderTargetViews,
        ID3D11DepthStencilView *pDepthStencilView);

    virtual void STDMETHODCALLTYPE OMSetRenderTargetsAndUnorderedAccessViews( 
        UINT NumRTVs,
        ID3D11RenderTargetView *const *ppRenderTargetViews,
        ID3D11DepthStencilView *pDepthStencilView,
        UINT UAVStartSlot,
        UINT NumUAVs,
        ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
        const UINT *pUAVInitialCounts);

    virtual void STDMETHODCALLTYPE OMSetBlendState( 
        ID3D11BlendState *pBlendState,
        const FLOAT BlendFactor[ 4 ],
        UINT SampleMask);

    virtual void STDMETHODCALLTYPE OMSetDepthStencilState( 
        ID3D11DepthStencilState *pDepthStencilState,
        UINT StencilRef);

    virtual void STDMETHODCALLTYPE SOSetTargets( 
        UINT NumBuffers,
        ID3D11Buffer *const *ppSOTargets,
        const UINT *pOffsets);

    virtual void STDMETHODCALLTYPE DrawAuto( void);

    virtual void STDMETHODCALLTYPE DrawIndexedInstancedIndirect( 
        ID3D11Buffer *pBufferForArgs,
        UINT AlignedByteOffsetForArgs);

    virtual void STDMETHODCALLTYPE DrawInstancedIndirect( 
        ID3D11Buffer *pBufferForArgs,
        UINT AlignedByteOffsetForArgs);

    virtual void STDMETHODCALLTYPE Dispatch( 
        UINT ThreadGroupCountX,
        UINT ThreadGroupCountY,
        UINT ThreadGroupCountZ);

    virtual void STDMETHODCALLTYPE DispatchIndirect( 
        ID3D11Buffer *pBufferForArgs,
        UINT AlignedByteOffsetForArgs);

    virtual void STDMETHODCALLTYPE RSSetState( 
        ID3D11RasterizerState *pRasterizerState);

    virtual void STDMETHODCALLTYPE RSSetViewports( 
        UINT NumViewports,
        const D3D11_VIEWPORT *pViewports);

    virtual void STDMETHODCALLTYPE RSSetScissorRects( 
        UINT NumRects,
        const D3D11_RECT *pRects);

    virtual void STDMETHODCALLTYPE CopySubresourceRegion( 
        ID3D11Resource *pDstResource,
        UINT DstSubresource,
        UINT DstX,
        UINT DstY,
        UINT DstZ,
        ID3D11Resource *pSrcResource,
        UINT SrcSubresource,
        const D3D11_BOX *pSrcBox);

    virtual void STDMETHODCALLTYPE CopyResource( 
        ID3D11Resource *pDstResource,
        ID3D11Resource *pSrcResource);

    virtual void STDMETHODCALLTYPE UpdateSubresource( 
        ID3D11Resource *pDstResource,
        UINT DstSubresource,
        const D3D11_BOX *pDstBox,
        const void *pSrcData,
        UINT SrcRowPitch,
        UINT SrcDepthPitch);

    virtual void STDMETHODCALLTYPE CopyStructureCount( 
        ID3D11Buffer *pDstBuffer,
        UINT DstAlignedByteOffset,
        ID3D11UnorderedAccessView *pSrcView);

    virtual void STDMETHODCALLTYPE ClearRenderTargetView( 
        ID3D11RenderTargetView *pRenderTargetView,
        const FLOAT ColorRGBA[ 4 ]);

    virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewUint( 
        ID3D11UnorderedAccessView *pUnorderedAccessView,
        const UINT Values[ 4 ]);

    virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat( 
        ID3D11UnorderedAccessView *pUnorderedAccessView,
        const FLOAT Values[ 4 ]);

    virtual void STDMETHODCALLTYPE ClearDepthStencilView( 
        ID3D11DepthStencilView *pDepthStencilView,
        UINT ClearFlags,
        FLOAT Depth,
        UINT8 Stencil);

    virtual void STDMETHODCALLTYPE GenerateMips( 
        ID3D11ShaderResourceView *pShaderResourceView);

    virtual void STDMETHODCALLTYPE SetResourceMinLOD( 
        ID3D11Resource *pResource,
        FLOAT MinLOD);

    virtual FLOAT STDMETHODCALLTYPE GetResourceMinLOD( 
        ID3D11Resource *pResource);

    virtual void STDMETHODCALLTYPE ResolveSubresource( 
        ID3D11Resource *pDstResource,
        UINT DstSubresource,
        ID3D11Resource *pSrcResource,
        UINT SrcSubresource,
        DXGI_FORMAT Format);

    virtual void STDMETHODCALLTYPE ExecuteCommandList( 
        ID3D11CommandList *pCommandList,
        BOOL RestoreContextState);

    virtual void STDMETHODCALLTYPE HSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE HSSetShader( 
        ID3D11HullShader *pHullShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE HSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE HSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE DSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE DSSetShader( 
        ID3D11DomainShader *pDomainShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE DSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE DSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE CSSetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView *const *ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE CSSetUnorderedAccessViews( 
        UINT StartSlot,
        UINT NumUAVs,
        ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
        const UINT *pUAVInitialCounts);

    virtual void STDMETHODCALLTYPE CSSetShader( 
        ID3D11ComputeShader *pComputeShader,
        ID3D11ClassInstance *const *ppClassInstances,
        UINT NumClassInstances);

    virtual void STDMETHODCALLTYPE CSSetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState *const *ppSamplers);

    virtual void STDMETHODCALLTYPE CSSetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer *const *ppConstantBuffers);

    virtual void STDMETHODCALLTYPE VSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE PSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE PSGetShader( 
        ID3D11PixelShader **ppPixelShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE PSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE VSGetShader( 
        ID3D11VertexShader **ppVertexShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE PSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE IAGetInputLayout( 
        ID3D11InputLayout **ppInputLayout);

    virtual void STDMETHODCALLTYPE IAGetVertexBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppVertexBuffers,
        UINT *pStrides,
        UINT *pOffsets);

    virtual void STDMETHODCALLTYPE IAGetIndexBuffer( 
        ID3D11Buffer **pIndexBuffer,
        DXGI_FORMAT *Format,
        UINT *Offset);

    virtual void STDMETHODCALLTYPE GSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE GSGetShader( 
        ID3D11GeometryShader **ppGeometryShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE IAGetPrimitiveTopology( 
        D3D11_PRIMITIVE_TOPOLOGY *pTopology);

    virtual void STDMETHODCALLTYPE VSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE VSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE GetPredication( 
        ID3D11Predicate **ppPredicate,
        BOOL *pPredicateValue);

    virtual void STDMETHODCALLTYPE GSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE GSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE OMGetRenderTargets( 
        UINT NumViews,
        ID3D11RenderTargetView **ppRenderTargetViews,
        ID3D11DepthStencilView **ppDepthStencilView);

    virtual void STDMETHODCALLTYPE OMGetRenderTargetsAndUnorderedAccessViews( 
        UINT NumRTVs,
        ID3D11RenderTargetView **ppRenderTargetViews,
        ID3D11DepthStencilView **ppDepthStencilView,
        UINT UAVStartSlot,
        UINT NumUAVs,
        ID3D11UnorderedAccessView **ppUnorderedAccessViews);

    virtual void STDMETHODCALLTYPE OMGetBlendState( 
        ID3D11BlendState **ppBlendState,
        FLOAT BlendFactor[ 4 ],
        UINT *pSampleMask);

    virtual void STDMETHODCALLTYPE OMGetDepthStencilState( 
        ID3D11DepthStencilState **ppDepthStencilState,
        UINT *pStencilRef);

    virtual void STDMETHODCALLTYPE SOGetTargets( 
        UINT NumBuffers,
        ID3D11Buffer **ppSOTargets);

    virtual void STDMETHODCALLTYPE RSGetState( 
        ID3D11RasterizerState **ppRasterizerState);

    virtual void STDMETHODCALLTYPE RSGetViewports( 
        UINT *pNumViewports,
        D3D11_VIEWPORT *pViewports);

    virtual void STDMETHODCALLTYPE RSGetScissorRects( 
        UINT *pNumRects,
        D3D11_RECT *pRects);

    virtual void STDMETHODCALLTYPE HSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE HSGetShader( 
        ID3D11HullShader **ppHullShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE HSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE HSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE DSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE DSGetShader( 
        ID3D11DomainShader **ppDomainShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE DSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE DSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE CSGetShaderResources( 
        UINT StartSlot,
        UINT NumViews,
        ID3D11ShaderResourceView **ppShaderResourceViews);

    virtual void STDMETHODCALLTYPE CSGetUnorderedAccessViews( 
        UINT StartSlot,
        UINT NumUAVs,
        ID3D11UnorderedAccessView **ppUnorderedAccessViews);

    virtual void STDMETHODCALLTYPE CSGetShader( 
        ID3D11ComputeShader **ppComputeShader,
        ID3D11ClassInstance **ppClassInstances,
        UINT *pNumClassInstances);

    virtual void STDMETHODCALLTYPE CSGetSamplers( 
        UINT StartSlot,
        UINT NumSamplers,
        ID3D11SamplerState **ppSamplers);

    virtual void STDMETHODCALLTYPE CSGetConstantBuffers( 
        UINT StartSlot,
        UINT NumBuffers,
        ID3D11Buffer **ppConstantBuffers);

    virtual void STDMETHODCALLTYPE ClearState( void);

    virtual void STDMETHODCALLTYPE Flush( void);

    virtual D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE GetType( void);

    virtual UINT STDMETHODCALLTYPE GetContextFlags( void);

    virtual HRESULT STDMETHODCALLTYPE FinishCommandList( 
        BOOL RestoreDeferredContextState,
        ID3D11CommandList **ppCommandList);
};

#endif // _LazyD3D11DeviceContext_h_
