#include "LazyD3D11DeviceContext.h"
#include <algorithm>



LazyD3D11DeviceContext::RenderStates::RenderStates()
{
    // no problem!
    memset(this, 0, sizeof(*this));
}


ID3D11DeviceContext* LazyD3D11DeviceContext::Create( ID3D11DeviceContext *_super )
{
    return new LazyD3D11DeviceContext(_super);
}


void LazyD3D11DeviceContext::AcualSetRenderState()
{
    // todo: Å¬ range ‚¾‚¯XV

    if(m_rs.PSShader!=m_rs_prev.PSShader || m_rs.PSClassInstances!=m_rs_prev.PSClassInstances || m_rs.PSNumClassInstances!=m_rs_prev.PSNumClassInstances) {
        m_super->PSSetShader(m_rs.PSShader, m_rs.PSClassInstances, m_rs.PSNumClassInstances);
    }
    if(m_rs.VSShader!=m_rs_prev.VSShader || m_rs.VSClassInstances!=m_rs_prev.VSClassInstances || m_rs.VSNumClassInstances!=m_rs_prev.VSNumClassInstances) {
        m_super->VSSetShader(m_rs.VSShader, m_rs.VSClassInstances, m_rs.VSNumClassInstances);
    }
    if(m_rs.GSShader!=m_rs_prev.GSShader || m_rs.GSClassInstances!=m_rs_prev.GSClassInstances || m_rs.GSNumClassInstances!=m_rs_prev.GSNumClassInstances) {
        m_super->GSSetShader(m_rs.GSShader, m_rs.GSClassInstances, m_rs.GSNumClassInstances);
    }
    if(m_rs.HSShader!=m_rs_prev.HSShader || m_rs.HSClassInstances!=m_rs_prev.HSClassInstances || m_rs.HSNumClassInstances!=m_rs_prev.HSNumClassInstances) {
        m_super->HSSetShader(m_rs.HSShader, m_rs.HSClassInstances, m_rs.HSNumClassInstances);
    }
    if(m_rs.DSShader!=m_rs_prev.DSShader || m_rs.DSClassInstances!=m_rs_prev.DSClassInstances || m_rs.DSNumClassInstances!=m_rs_prev.DSNumClassInstances) {
        m_super->DSSetShader(m_rs.DSShader, m_rs.DSClassInstances, m_rs.DSNumClassInstances);
    }
    if(m_rs.CSShader!=m_rs_prev.CSShader || m_rs.CSClassInstances!=m_rs_prev.CSClassInstances || m_rs.CSNumClassInstances!=m_rs_prev.CSNumClassInstances) {
        m_super->CSSetShader(m_rs.CSShader, m_rs.CSClassInstances, m_rs.CSNumClassInstances);
    }

    if(!std::equal(m_rs.PSShaderResources, m_rs.PSShaderResources+_countof(m_rs.PSShaderResources), m_rs_prev.PSShaderResources)) {
        m_super->PSSetShaderResources(0, _countof(m_rs.PSShaderResources), m_rs.PSShaderResources);
    }
    if(!std::equal(m_rs.VSShaderResources, m_rs.VSShaderResources+_countof(m_rs.VSShaderResources), m_rs_prev.VSShaderResources)) {
        m_super->VSSetShaderResources(0, _countof(m_rs.VSShaderResources), m_rs.VSShaderResources);
    }
    if(!std::equal(m_rs.GSShaderResources, m_rs.GSShaderResources+_countof(m_rs.GSShaderResources), m_rs_prev.GSShaderResources)) {
        m_super->GSSetShaderResources(0, _countof(m_rs.GSShaderResources), m_rs.GSShaderResources);
    }
    if(!std::equal(m_rs.HSShaderResources, m_rs.HSShaderResources+_countof(m_rs.HSShaderResources), m_rs_prev.HSShaderResources)) {
        m_super->HSSetShaderResources(0, _countof(m_rs.HSShaderResources), m_rs.HSShaderResources);
    }
    if(!std::equal(m_rs.DSShaderResources, m_rs.DSShaderResources+_countof(m_rs.DSShaderResources), m_rs_prev.DSShaderResources)) {
        m_super->DSSetShaderResources(0, _countof(m_rs.DSShaderResources), m_rs.DSShaderResources);
    }
    if(!std::equal(m_rs.CSShaderResources, m_rs.CSShaderResources+_countof(m_rs.CSShaderResources), m_rs_prev.CSShaderResources)) {
        m_super->CSSetShaderResources(0, _countof(m_rs.CSShaderResources), m_rs.CSShaderResources);
    }

    if(!std::equal(m_rs.PSConstantBuffers, m_rs.PSConstantBuffers+_countof(m_rs.PSConstantBuffers), m_rs_prev.PSConstantBuffers)) {
        m_super->PSSetConstantBuffers(0, _countof(m_rs.PSConstantBuffers), m_rs.PSConstantBuffers);
    }
    if(!std::equal(m_rs.VSConstantBuffers, m_rs.VSConstantBuffers+_countof(m_rs.VSConstantBuffers), m_rs_prev.VSConstantBuffers)) {
        m_super->VSSetConstantBuffers(0, _countof(m_rs.VSConstantBuffers), m_rs.VSConstantBuffers);
    }
    if(!std::equal(m_rs.GSConstantBuffers, m_rs.GSConstantBuffers+_countof(m_rs.GSConstantBuffers), m_rs_prev.GSConstantBuffers)) {
        m_super->GSSetConstantBuffers(0, _countof(m_rs.GSConstantBuffers), m_rs.GSConstantBuffers);
    }
    if(!std::equal(m_rs.HSConstantBuffers, m_rs.HSConstantBuffers+_countof(m_rs.HSConstantBuffers), m_rs_prev.HSConstantBuffers)) {
        m_super->HSSetConstantBuffers(0, _countof(m_rs.HSConstantBuffers), m_rs.HSConstantBuffers);
    }
    if(!std::equal(m_rs.DSConstantBuffers, m_rs.DSConstantBuffers+_countof(m_rs.DSConstantBuffers), m_rs_prev.DSConstantBuffers)) {
        m_super->DSSetConstantBuffers(0, _countof(m_rs.DSConstantBuffers), m_rs.DSConstantBuffers);
    }
    if(!std::equal(m_rs.CSConstantBuffers, m_rs.CSConstantBuffers+_countof(m_rs.CSConstantBuffers), m_rs_prev.CSConstantBuffers)) {
        m_super->CSSetConstantBuffers(0, _countof(m_rs.CSConstantBuffers), m_rs.CSConstantBuffers);
    }

    if(!std::equal(m_rs.PSSamplers, m_rs.PSSamplers+_countof(m_rs.PSSamplers), m_rs_prev.PSSamplers)) {
        m_super->PSSetSamplers(0, _countof(m_rs.PSSamplers), m_rs.PSSamplers);
    }
    if(!std::equal(m_rs.VSSamplers, m_rs.VSSamplers+_countof(m_rs.VSSamplers), m_rs_prev.VSSamplers)) {
        m_super->VSSetSamplers(0, _countof(m_rs.VSSamplers), m_rs.VSSamplers);
    }
    if(!std::equal(m_rs.GSSamplers, m_rs.GSSamplers+_countof(m_rs.GSSamplers), m_rs_prev.GSSamplers)) {
        m_super->GSSetSamplers(0, _countof(m_rs.GSSamplers), m_rs.GSSamplers);
    }
    if(!std::equal(m_rs.HSSamplers, m_rs.HSSamplers+_countof(m_rs.HSSamplers), m_rs_prev.HSSamplers)) {
        m_super->HSSetSamplers(0, _countof(m_rs.HSSamplers), m_rs.HSSamplers);
    }
    if(!std::equal(m_rs.DSSamplers, m_rs.DSSamplers+_countof(m_rs.DSSamplers), m_rs_prev.DSSamplers)) {
        m_super->DSSetSamplers(0, _countof(m_rs.DSSamplers), m_rs.DSSamplers);
    }
    if(!std::equal(m_rs.CSSamplers, m_rs.CSSamplers+_countof(m_rs.CSSamplers), m_rs_prev.CSSamplers)) {
        m_super->CSSetSamplers(0, _countof(m_rs.CSSamplers), m_rs.CSSamplers);
    }

    if(m_rs.IAPrimitiveTopology!=m_rs_prev.IAPrimitiveTopology) {
        m_super->IASetPrimitiveTopology(m_rs.IAPrimitiveTopology);
    }
    if(m_rs.IAInputLayout!=m_rs_prev.IAInputLayout) {
        m_super->IASetInputLayout(m_rs.IAInputLayout);
    }
    if( m_rs.IAIndexBuffer!=m_rs_prev.IAIndexBuffer ||
        m_rs.IAIndexBufferFormat!=m_rs_prev.IAIndexBufferFormat ||
        m_rs.IAIndexBufferOffset!=m_rs_prev.IAIndexBufferOffset )
    {
        m_super->IASetIndexBuffer(m_rs.IAIndexBuffer, m_rs.IAIndexBufferFormat, m_rs.IAIndexBufferOffset);
    }
    if( !std::equal(m_rs.IAVertexBuffers, m_rs.IAVertexBuffers+_countof(m_rs.IAVertexBuffers), m_rs_prev.IAVertexBuffers) ||
        !std::equal(m_rs.IAVertexBufferStrides, m_rs.IAVertexBufferStrides+_countof(m_rs.IAVertexBufferStrides), m_rs_prev.IAVertexBufferStrides) ||
        !std::equal(m_rs.IAVertexBufferOffsets, m_rs.IAVertexBufferOffsets+_countof(m_rs.IAVertexBufferOffsets), m_rs_prev.IAVertexBufferOffsets) )
    {
        m_super->IASetVertexBuffers(0, _countof(m_rs.IAVertexBuffers), m_rs.IAVertexBuffers, m_rs.IAVertexBufferStrides, m_rs.IAVertexBufferOffsets);
    }

    if( !std::equal(m_rs.OMUnorderedAccesses, m_rs.OMUnorderedAccesses+_countof(m_rs.OMUnorderedAccesses), m_rs_prev.OMUnorderedAccesses) ||
        !std::equal(m_rs.OMUnorderedInitialCounts, m_rs.OMUnorderedInitialCounts+_countof(m_rs.OMUnorderedInitialCounts), m_rs_prev.OMUnorderedInitialCounts) )
    {
        m_super->OMSetRenderTargetsAndUnorderedAccessViews(
            m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil,
            0, _countof(m_rs.OMUnorderedAccesses), m_rs.OMUnorderedAccesses, m_rs.OMUnorderedInitialCounts);
    }
    else
    if( m_rs.OMNumRenderTargets!=m_rs_prev.OMNumRenderTargets ||
        !std::equal(m_rs.OMRenderTargets, m_rs.OMRenderTargets+m_rs.OMNumRenderTargets, m_rs_prev.OMRenderTargets) ||
        m_rs.OMDepthStencil!=m_rs_prev.OMDepthStencil  )
    {
        m_super->OMSetRenderTargets(m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil);
    }
    if( m_rs.OMBlendState!=m_rs_prev.OMBlendState ||
        !std::equal(m_rs.OMBlendFactor, m_rs.OMBlendFactor+_countof(m_rs.OMBlendFactor), m_rs_prev.OMBlendFactor) ||
        m_rs.OMBlendSampleMask, m_rs_prev.OMBlendSampleMask)
    {
        m_super->OMSetBlendState(m_rs.OMBlendState, m_rs.OMBlendFactor, m_rs.OMBlendSampleMask);
    }
    if(m_rs.OMDepthStencilState!=m_rs_prev.OMDepthStencilState || m_rs.OMStencilRef!=m_rs_prev.OMStencilRef) {
        m_super->OMSetDepthStencilState(m_rs.OMDepthStencilState, m_rs.OMStencilRef);
    }

    if( !std::equal(m_rs.SOTargets, m_rs.SOTargets+_countof(m_rs.SOTargets), m_rs_prev.SOTargets) ||
        !std::equal(m_rs.SOOffsets, m_rs.SOOffsets+_countof(m_rs.SOOffsets), m_rs_prev.SOOffsets) )
    {
        m_rs.SOTargets;
        m_super->SOSetTargets(_countof(m_rs.SOTargets), m_rs.SOTargets, m_rs.SOOffsets);
    }

    if(m_rs.RSRasterState!=m_rs_prev.RSRasterState) {
        m_super->RSSetState(m_rs.RSRasterState);
    }
    if( m_rs.RSNumViewports!=m_rs_prev.RSNumViewports ||
        !std::equal(m_rs.RSViewports, m_rs.RSViewports+m_rs.RSNumViewports, m_rs_prev.RSViewports) )
    {
        m_super->RSSetViewports(m_rs.RSNumViewports, m_rs.RSViewports);
    }
    if( m_rs.RSNumScissorRects!=m_rs_prev.RSNumScissorRects ||
        !std::equal(m_rs.RSScissorRects, m_rs.RSScissorRects+m_rs.RSNumScissorRects, m_rs_prev.RSScissorRects) )
    {
        m_super->RSSetScissorRects(m_rs.RSNumScissorRects, m_rs.RSScissorRects);
    }


    m_rs_prev = m_rs;
}

LazyD3D11DeviceContext::LazyD3D11DeviceContext( ID3D11DeviceContext *_super )
    : m_super(_super)
{
}





HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::QueryInterface( REFIID riid, __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject )
{
    HRESULT r = m_super->QueryInterface(riid, ppvObject);
    return r;
}

ULONG STDMETHODCALLTYPE LazyD3D11DeviceContext::AddRef( void )
{
    ULONG r = m_super->AddRef();
    return r;
}

ULONG STDMETHODCALLTYPE LazyD3D11DeviceContext::Release( void )
{
    ULONG r = m_super->Release();
    if(r==0) { delete this; }
    return r;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GetDevice( ID3D11Device **ppDevice )
{
    m_super->GetDevice(ppDevice);
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::GetPrivateData( REFGUID guid, UINT *pDataSize, void *pData )
{
    HRESULT r = m_super->GetPrivateData(guid, pDataSize, pData);
    return r;
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::SetPrivateData( REFGUID guid, UINT DataSize, const void *pData )
{
    HRESULT r = m_super->SetPrivateData(guid, DataSize, pData);
    return r;
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::SetPrivateDataInterface( REFGUID guid, const IUnknown *pData )
{
    HRESULT r = m_super->SetPrivateDataInterface(guid, pData);
    return r;
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.VSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.PSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShader( ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.PSShader = pPixelShader;
    m_rs.PSClassInstances = ppClassInstances;
    m_rs.PSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.PSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShader( ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.VSShader = pVertexShader;
    m_rs.VSClassInstances = ppClassInstances;
    m_rs.VSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexed( UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation )
{
    AcualSetRenderState();
    m_super->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Draw( UINT VertexCount, UINT StartVertexLocation )
{
    AcualSetRenderState();
    m_super->Draw(VertexCount, StartVertexLocation);
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::Map( ID3D11Resource *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource )
{
    HRESULT r = m_super->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
    return r;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Unmap( ID3D11Resource *pResource, UINT Subresource )
{
    m_super->Unmap(pResource, Subresource);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.PSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetInputLayout( ID3D11InputLayout *pInputLayout )
{
    m_rs.IAInputLayout = pInputLayout;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetVertexBuffers(  UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppVertexBuffers, const UINT *pStrides, const UINT *pOffsets )
{
    std::copy(ppVertexBuffers, ppVertexBuffers+NumBuffers, m_rs.IAVertexBuffers+StartSlot);
    std::copy(pStrides, pStrides+NumBuffers, m_rs.IAVertexBufferStrides+StartSlot);
    std::copy(pOffsets, pOffsets+NumBuffers, m_rs.IAVertexBufferOffsets+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetIndexBuffer(  ID3D11Buffer *pIndexBuffer, DXGI_FORMAT Format, UINT Offset )
{
    m_rs.IAIndexBuffer = pIndexBuffer;
    m_rs.IAIndexBufferFormat = Format;
    m_rs.IAIndexBufferOffset = Offset;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexedInstanced( UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation )
{
    AcualSetRenderState();
    m_super->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawInstanced( UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation )
{
    AcualSetRenderState();
    m_super->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.GSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetShader( ID3D11GeometryShader *pShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.GSShader = pShader;
    m_rs.GSClassInstances = ppClassInstances;
    m_rs.GSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY Topology )
{
    m_rs.IAPrimitiveTopology = Topology;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.VSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.VSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Begin( ID3D11Asynchronous *pAsync )
{
    m_super->Begin(pAsync);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::End( ID3D11Asynchronous *pAsync )
{
    m_super->End(pAsync);
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::GetData( ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags )
{
    HRESULT r = m_super->GetData(pAsync, pData, DataSize, GetDataFlags);
    return r;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SetPredication( ID3D11Predicate *pPredicate, BOOL PredicateValue )
{
    m_super->SetPredication(pPredicate, PredicateValue);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.GSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.GSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargets( UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView)
{
    m_rs.OMNumRenderTargets = NumViews;
    std::copy(ppRenderTargetViews, ppRenderTargetViews+NumViews, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(  UINT NumRTVs, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts)
{
    m_rs.OMNumRenderTargets = NumRTVs;
    std::copy(ppRenderTargetViews, ppRenderTargetViews+NumRTVs, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;

    std::copy(ppUnorderedAccessViews, ppUnorderedAccessViews+NumUAVs, m_rs.OMUnorderedAccesses+UAVStartSlot);
    std::copy(pUAVInitialCounts, pUAVInitialCounts+NumUAVs, m_rs.OMUnorderedInitialCounts+UAVStartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetBlendState( ID3D11BlendState *pBlendState, const FLOAT BlendFactor[ 4 ], UINT SampleMask )
{
    m_rs.OMBlendState = pBlendState;
    std::copy(BlendFactor, BlendFactor+_countof(m_rs.OMBlendFactor), m_rs.OMBlendFactor);
    m_rs.OMBlendSampleMask = SampleMask;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetDepthStencilState( ID3D11DepthStencilState *pDepthStencilState, UINT StencilRef )
{
    m_rs.OMDepthStencilState = pDepthStencilState;
    m_rs.OMStencilRef = StencilRef;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOSetTargets( UINT NumBuffers, ID3D11Buffer *const *ppSOTargets, const UINT *pOffsets )
{
    std::copy(ppSOTargets, ppSOTargets+NumBuffers, m_rs.SOTargets);
    std::copy(pOffsets, pOffsets+NumBuffers, m_rs.SOOffsets);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawAuto( void )
{
    AcualSetRenderState();
    m_super->DrawAuto();
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexedInstancedIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    AcualSetRenderState();
    m_super->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawInstancedIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    AcualSetRenderState();
    m_super->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Dispatch( UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ )
{
    AcualSetRenderState();
    m_super->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DispatchIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    AcualSetRenderState();
    m_super->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSSetState( ID3D11RasterizerState *pRasterizerState )
{
    m_super->RSSetState(pRasterizerState);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSSetViewports( UINT NumViewports, const D3D11_VIEWPORT *pViewports )
{
    m_rs.RSNumViewports = NumViewports;
    std::copy(pViewports, pViewports+NumViewports, m_rs.RSViewports);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSSetScissorRects( UINT NumRects, const D3D11_RECT *pRects )
{
    m_rs.RSNumScissorRects = NumRects;
    std::copy(pRects, pRects+NumRects, m_rs.RSScissorRects);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopySubresourceRegion( ID3D11Resource *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource *pSrcResource, UINT SrcSubresource, const D3D11_BOX *pSrcBox )
{
    m_super->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopyResource( ID3D11Resource *pDstResource, ID3D11Resource *pSrcResource )
{
    m_super->CopyResource(pDstResource, pSrcResource);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::UpdateSubresource( ID3D11Resource *pDstResource, UINT DstSubresource, const D3D11_BOX *pDstBox, const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch )
{
    m_super->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopyStructureCount( ID3D11Buffer *pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView *pSrcView )
{
    m_super->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearRenderTargetView( ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[ 4 ] )
{
    m_super->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearUnorderedAccessViewUint( ID3D11UnorderedAccessView *pUnorderedAccessView, const UINT Values[ 4 ] )
{
    m_super->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearUnorderedAccessViewFloat( ID3D11UnorderedAccessView *pUnorderedAccessView, const FLOAT Values[ 4 ] )
{
    m_super->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearDepthStencilView( ID3D11DepthStencilView *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil )
{
    m_super->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GenerateMips( ID3D11ShaderResourceView *pShaderResourceView )
{
    m_super->GenerateMips(pShaderResourceView);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SetResourceMinLOD( ID3D11Resource *pResource, FLOAT MinLOD )
{
    m_super->SetResourceMinLOD(pResource, MinLOD);
}

FLOAT STDMETHODCALLTYPE LazyD3D11DeviceContext::GetResourceMinLOD( ID3D11Resource *pResource )
{
    FLOAT r = m_super->GetResourceMinLOD(pResource);
    return r;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ResolveSubresource( ID3D11Resource *pDstResource, UINT DstSubresource, ID3D11Resource *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format )
{
    m_super->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ExecuteCommandList( ID3D11CommandList *pCommandList, BOOL RestoreContextState )
{
    m_super->ExecuteCommandList(pCommandList, RestoreContextState);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.HSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetShader( ID3D11HullShader *pHullShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.HSShader = pHullShader;
    m_rs.HSClassInstances = ppClassInstances;
    m_rs.HSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.HSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.HSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.DSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShader( ID3D11DomainShader *pDomainShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.DSShader = pDomainShader;
    m_rs.DSClassInstances = ppClassInstances;
    m_rs.DSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.DSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.DSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    std::copy(ppShaderResourceViews, ppShaderResourceViews+NumViews, m_rs.CSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts )
{
    m_super->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShader( ID3D11ComputeShader *pComputeShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_rs.CSShader = pComputeShader;
    m_rs.CSClassInstances = ppClassInstances;
    m_rs.CSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    std::copy(ppSamplers, ppSamplers+NumSamplers, m_rs.CSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    std::copy(ppConstantBuffers, ppConstantBuffers+NumBuffers, m_rs.CSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    m_super->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShader( ID3D11PixelShader **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShader( ID3D11VertexShader **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetInputLayout( ID3D11InputLayout **ppInputLayout )
{
    m_super->IAGetInputLayout(ppInputLayout);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetVertexBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppVertexBuffers, UINT *pStrides, UINT *pOffsets )
{
    m_super->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetIndexBuffer( ID3D11Buffer **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset )
{
    m_super->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShader( ID3D11GeometryShader **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY *pTopology )
{
    m_super->IAGetPrimitiveTopology(pTopology);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    m_super->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GetPredication( ID3D11Predicate **ppPredicate, BOOL *pPredicateValue )
{
    m_super->GetPredication(ppPredicate, pPredicateValue);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    m_super->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargets( UINT NumViews, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView )
{
    m_super->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews( UINT NumRTVs, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    m_super->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetBlendState( ID3D11BlendState **ppBlendState, FLOAT BlendFactor[ 4 ], UINT *pSampleMask )
{
    m_super->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetDepthStencilState( ID3D11DepthStencilState **ppDepthStencilState, UINT *pStencilRef )
{
    m_super->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOGetTargets( UINT NumBuffers, ID3D11Buffer **ppSOTargets )
{
    m_super->SOGetTargets(NumBuffers, ppSOTargets);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetState( ID3D11RasterizerState **ppRasterizerState )
{
    m_super->RSGetState(ppRasterizerState);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetViewports( 
    UINT *pNumViewports,
    D3D11_VIEWPORT *pViewports)
{
    m_super->RSGetViewports(pNumViewports, pViewports);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetScissorRects( UINT *pNumRects, D3D11_RECT *pRects )
{
    m_super->RSGetScissorRects(pNumRects, pRects);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShaderResources( 
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView **ppShaderResourceViews)
{
    m_super->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShader( ID3D11HullShader **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    m_super->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShader( ID3D11DomainShader **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    m_super->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    m_super->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShader( ID3D11ComputeShader **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    m_super->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    m_super->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    m_super->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearState( void )
{
    m_super->ClearState();
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Flush( void )
{
    m_super->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE LazyD3D11DeviceContext::GetType( void )
{
    D3D11_DEVICE_CONTEXT_TYPE r = m_super->GetType();
    return r;
}

UINT STDMETHODCALLTYPE LazyD3D11DeviceContext::GetContextFlags( void )
{
    UINT r = m_super->GetContextFlags();
    return r;
}

HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::FinishCommandList( BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList )
{
    HRESULT r = m_super->FinishCommandList(RestoreDeferredContextState, ppCommandList);
    return r;
}
