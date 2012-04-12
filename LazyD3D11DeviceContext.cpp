#include "LazyD3D11DeviceContext.h"
#include <algorithm>

template<class Iter>
inline bool equal_n(Iter first1, int n, Iter first2)
{
    return std::equal(first1, first1+n, first2);
}

using std::copy_n;

template<class Iter>
inline void addref_and_copy_n(Iter first1, int n, Iter first2)
{
    Iter last1 = first1 + n;
    for(Iter i=first1; i!=last1; ++i) {
        (*i)->AddRef();
    }
    copy_n(first1, n, first2);
}




LazyD3D11DeviceContext::RenderStates::RenderStates()
{
    // no problem!
    memset(this, 0, sizeof(*this));
}
LazyD3D11DeviceContext::CallStates::CallStates()
{
    clear();
}

void LazyD3D11DeviceContext::CallStates::clear()
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
    if(m_cs.PSSetShader) {
        if(m_rs.PSShader!=m_rs_prev.PSShader || m_rs.PSNumClassInstances!=m_rs_prev.PSNumClassInstances ||
            !equal_n(m_rs.PSClassInstances, m_rs.PSNumClassInstances, m_rs_prev.PSClassInstances) )
        {
            m_super->PSSetShader(m_rs.PSShader, m_rs.PSClassInstances, m_rs.PSNumClassInstances);
        }
    }
    if(m_cs.VSSetShader) {
        if(m_rs.VSShader!=m_rs_prev.VSShader || m_rs.VSNumClassInstances!=m_rs_prev.VSNumClassInstances ||
            !equal_n(m_rs.VSClassInstances, m_rs.VSNumClassInstances, m_rs_prev.VSClassInstances) )
        {
            m_super->VSSetShader(m_rs.VSShader, m_rs.VSClassInstances, m_rs.VSNumClassInstances);
        }
    }
    if(m_cs.GSSetShader) {
        if(m_rs.GSShader!=m_rs_prev.GSShader || m_rs.GSNumClassInstances!=m_rs_prev.GSNumClassInstances ||
            !equal_n(m_rs.GSClassInstances, m_rs.GSNumClassInstances, m_rs_prev.GSClassInstances) )
        {
            m_super->GSSetShader(m_rs.GSShader, m_rs.GSClassInstances, m_rs.GSNumClassInstances);
        }
    }
    if(m_cs.HSSetShader) {
        if(m_rs.HSShader!=m_rs_prev.HSShader || m_rs.HSNumClassInstances!=m_rs_prev.HSNumClassInstances ||
            !equal_n(m_rs.HSClassInstances, m_rs.HSNumClassInstances, m_rs_prev.HSClassInstances) )
        {
            m_super->HSSetShader(m_rs.HSShader, m_rs.HSClassInstances, m_rs.HSNumClassInstances);
        }
    }
    if(m_cs.DSSetShader) {
        if(m_rs.DSShader!=m_rs_prev.DSShader || m_rs.DSNumClassInstances!=m_rs_prev.DSNumClassInstances ||
            !equal_n(m_rs.DSClassInstances, m_rs.DSNumClassInstances, m_rs_prev.DSClassInstances) )
        {
            m_super->DSSetShader(m_rs.DSShader, m_rs.DSClassInstances, m_rs.DSNumClassInstances);
        }
    }
    if(m_cs.CSSetShader) {
        if(m_rs.CSShader!=m_rs_prev.CSShader || m_rs.CSNumClassInstances!=m_rs_prev.CSNumClassInstances ||
            !equal_n(m_rs.CSClassInstances, m_rs.CSNumClassInstances, m_rs_prev.CSClassInstances) )
        {
            m_super->CSSetShader(m_rs.CSShader, m_rs.CSClassInstances, m_rs.CSNumClassInstances);
        }
    }


    if(m_cs.PSSetShaderResources) {
        if(!equal_n(m_rs.PSShaderResources, _countof(m_rs.PSShaderResources), m_rs_prev.PSShaderResources)) {
            m_super->PSSetShaderResources(0, _countof(m_rs.PSShaderResources), m_rs.PSShaderResources);
        }
    }
    if(m_cs.VSSetShaderResources) {
        if(!equal_n(m_rs.VSShaderResources, _countof(m_rs.VSShaderResources), m_rs_prev.VSShaderResources)) {
            m_super->VSSetShaderResources(0, _countof(m_rs.VSShaderResources), m_rs.VSShaderResources);
        }
    }
    if(m_cs.GSSetShaderResources) {
        if(!equal_n(m_rs.GSShaderResources, _countof(m_rs.GSShaderResources), m_rs_prev.GSShaderResources)) {
            m_super->GSSetShaderResources(0, _countof(m_rs.GSShaderResources), m_rs.GSShaderResources);
        }
    }
    if(m_cs.HSSetShaderResources) {
        if(!equal_n(m_rs.HSShaderResources, _countof(m_rs.HSShaderResources), m_rs_prev.HSShaderResources)) {
            m_super->HSSetShaderResources(0, _countof(m_rs.HSShaderResources), m_rs.HSShaderResources);
        }
    }
    if(m_cs.DSSetShaderResources) {
        if(!equal_n(m_rs.DSShaderResources, _countof(m_rs.DSShaderResources), m_rs_prev.DSShaderResources)) {
            m_super->DSSetShaderResources(0, _countof(m_rs.DSShaderResources), m_rs.DSShaderResources);
        }
    }
    if(m_cs.CSSetShaderResources) {
        if(!equal_n(m_rs.CSShaderResources, _countof(m_rs.CSShaderResources), m_rs_prev.CSShaderResources)) {
            m_super->CSSetShaderResources(0, _countof(m_rs.CSShaderResources), m_rs.CSShaderResources);
        }
    }


    if(m_cs.PSSetConstantBuffers) {
        if(!equal_n(m_rs.PSConstantBuffers, _countof(m_rs.PSConstantBuffers), m_rs_prev.PSConstantBuffers)) {
            m_super->PSSetConstantBuffers(0, _countof(m_rs.PSConstantBuffers), m_rs.PSConstantBuffers);
        }
    }
    if(m_cs.VSSetConstantBuffers) {
        if(!equal_n(m_rs.VSConstantBuffers, _countof(m_rs.VSConstantBuffers), m_rs_prev.VSConstantBuffers)) {
            m_super->VSSetConstantBuffers(0, _countof(m_rs.VSConstantBuffers), m_rs.VSConstantBuffers);
        }
    }
    if(m_cs.GSSetConstantBuffers) {
        if(!equal_n(m_rs.GSConstantBuffers, _countof(m_rs.GSConstantBuffers), m_rs_prev.GSConstantBuffers)) {
            m_super->GSSetConstantBuffers(0, _countof(m_rs.GSConstantBuffers), m_rs.GSConstantBuffers);
        }
    }
    if(m_cs.HSSetConstantBuffers) {
        if(!equal_n(m_rs.HSConstantBuffers, _countof(m_rs.HSConstantBuffers), m_rs_prev.HSConstantBuffers)) {
            m_super->HSSetConstantBuffers(0, _countof(m_rs.HSConstantBuffers), m_rs.HSConstantBuffers);
        }
    }
    if(m_cs.DSSetConstantBuffers) {
        if(!equal_n(m_rs.DSConstantBuffers, _countof(m_rs.DSConstantBuffers), m_rs_prev.DSConstantBuffers)) {
            m_super->DSSetConstantBuffers(0, _countof(m_rs.DSConstantBuffers), m_rs.DSConstantBuffers);
        }
    }
    if(m_cs.CSSetConstantBuffers) {
        if(!equal_n(m_rs.CSConstantBuffers, _countof(m_rs.CSConstantBuffers), m_rs_prev.CSConstantBuffers)) {
            m_super->CSSetConstantBuffers(0, _countof(m_rs.CSConstantBuffers), m_rs.CSConstantBuffers);
        }
    }


    if(m_cs.PSSetSamplers) {
        if(!equal_n(m_rs.PSSamplers, _countof(m_rs.PSSamplers), m_rs_prev.PSSamplers)) {
            m_super->PSSetSamplers(0, _countof(m_rs.PSSamplers), m_rs.PSSamplers);
        }
    }
    if(m_cs.VSSetSamplers) {
        if(!equal_n(m_rs.VSSamplers, _countof(m_rs.VSSamplers), m_rs_prev.VSSamplers)) {
            m_super->VSSetSamplers(0, _countof(m_rs.VSSamplers), m_rs.VSSamplers);
        }
    }
    if(m_cs.GSSetSamplers) {
        if(!equal_n(m_rs.GSSamplers, _countof(m_rs.GSSamplers), m_rs_prev.GSSamplers)) {
            m_super->GSSetSamplers(0, _countof(m_rs.GSSamplers), m_rs.GSSamplers);
        }
    }
    if(m_cs.HSSetSamplers) {
        if(!equal_n(m_rs.HSSamplers, _countof(m_rs.HSSamplers), m_rs_prev.HSSamplers)) {
            m_super->HSSetSamplers(0, _countof(m_rs.HSSamplers), m_rs.HSSamplers);
        }
    }
    if(m_cs.DSSetSamplers) {
        if(!equal_n(m_rs.DSSamplers, _countof(m_rs.DSSamplers), m_rs_prev.DSSamplers)) {
            m_super->DSSetSamplers(0, _countof(m_rs.DSSamplers), m_rs.DSSamplers);
        }
    }
    if(m_cs.CSSetSamplers) {
        if(!equal_n(m_rs.CSSamplers, _countof(m_rs.CSSamplers), m_rs_prev.CSSamplers)) {
            m_super->CSSetSamplers(0, _countof(m_rs.CSSamplers), m_rs.CSSamplers);
        }
    }


    if(m_cs.CSSetUnorderedAccessViews) {
        if( !equal_n(m_rs.CSUnorderedAccesses, _countof(m_rs.CSUnorderedAccesses), m_rs_prev.CSUnorderedAccesses) ||
            !equal_n(m_rs.CSUnorderedInitialCounts, _countof(m_rs.CSUnorderedInitialCounts), m_rs_prev.CSUnorderedInitialCounts) )
        {
            m_super->CSSetUnorderedAccessViews(0, _countof(m_rs.CSUnorderedAccesses), m_rs.CSUnorderedAccesses, m_rs.CSUnorderedInitialCounts);
        }
    }


    if(m_cs.IASetInputLayout) {
        if(m_rs.IAInputLayout!=m_rs_prev.IAInputLayout) {
            m_super->IASetInputLayout(m_rs.IAInputLayout);
        }
    }
    if(m_cs.IASetVertexBuffers) {
        if( !equal_n(m_rs.IAVertexBuffers, _countof(m_rs.IAVertexBuffers), m_rs_prev.IAVertexBuffers) ||
            !equal_n(m_rs.IAVertexBufferStrides, _countof(m_rs.IAVertexBufferStrides), m_rs_prev.IAVertexBufferStrides) ||
            !equal_n(m_rs.IAVertexBufferOffsets, _countof(m_rs.IAVertexBufferOffsets), m_rs_prev.IAVertexBufferOffsets) )
        {
            m_super->IASetVertexBuffers(0, _countof(m_rs.IAVertexBuffers), m_rs.IAVertexBuffers, m_rs.IAVertexBufferStrides, m_rs.IAVertexBufferOffsets);
        }
    }
    if(m_cs.IASetIndexBuffer) {
        if( m_rs.IAIndexBuffer!=m_rs_prev.IAIndexBuffer ||
            m_rs.IAIndexBufferFormat!=m_rs_prev.IAIndexBufferFormat ||
            m_rs.IAIndexBufferOffset!=m_rs_prev.IAIndexBufferOffset )
        {
            m_super->IASetIndexBuffer(m_rs.IAIndexBuffer, m_rs.IAIndexBufferFormat, m_rs.IAIndexBufferOffset);
        }
    }
    if(m_cs.IASetPrimitiveTopology) {
        if(m_rs.IAPrimitiveTopology!=m_rs_prev.IAPrimitiveTopology) {
            m_super->IASetPrimitiveTopology(m_rs.IAPrimitiveTopology);
        }
    }


    if(m_cs.OMSetRenderTargets) {
        if( m_rs.OMNumRenderTargets!=m_rs_prev.OMNumRenderTargets ||
            !equal_n(m_rs.OMRenderTargets, m_rs.OMNumRenderTargets, m_rs_prev.OMRenderTargets) ||
            m_rs.OMDepthStencil!=m_rs_prev.OMDepthStencil  )
        {
            m_super->OMSetRenderTargets(m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil);
        }
    }
    if(m_cs.OMSetRenderTargetsAndUnorderedAccessViews) {
        if( !std::equal(m_rs.OMUnorderedAccesses, m_rs.OMUnorderedAccesses+_countof(m_rs.OMUnorderedAccesses), m_rs_prev.OMUnorderedAccesses) ||
            !std::equal(m_rs.OMUnorderedInitialCounts, m_rs.OMUnorderedInitialCounts+_countof(m_rs.OMUnorderedInitialCounts), m_rs_prev.OMUnorderedInitialCounts) )
        {
            m_super->OMSetRenderTargetsAndUnorderedAccessViews(
                m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil,
                0, _countof(m_rs.OMUnorderedAccesses), m_rs.OMUnorderedAccesses, m_rs.OMUnorderedInitialCounts);
        }
    }
    if(m_cs.OMSetBlendState) {
        if( m_rs.OMBlendState!=m_rs_prev.OMBlendState ||
            !equal_n(m_rs.OMBlendFactor, _countof(m_rs.OMBlendFactor), m_rs_prev.OMBlendFactor) ||
            m_rs.OMBlendSampleMask, m_rs_prev.OMBlendSampleMask)
        {
            m_super->OMSetBlendState(m_rs.OMBlendState, m_rs.OMBlendFactor, m_rs.OMBlendSampleMask);
        }
    }
    if(m_cs.OMSetDepthStencilState) {
        if(m_rs.OMDepthStencilState!=m_rs_prev.OMDepthStencilState || m_rs.OMStencilRef!=m_rs_prev.OMStencilRef) {
            m_super->OMSetDepthStencilState(m_rs.OMDepthStencilState, m_rs.OMStencilRef);
        }
    }


    if(m_cs.SOSetTargets) {
        if(m_cs.SOSetTargets) {
            if( !equal_n(m_rs.SOTargets, _countof(m_rs.SOTargets), m_rs_prev.SOTargets) ||
                !equal_n(m_rs.SOOffsets, _countof(m_rs.SOOffsets), m_rs_prev.SOOffsets) )
            {
                m_rs.SOTargets;
                m_super->SOSetTargets(_countof(m_rs.SOTargets), m_rs.SOTargets, m_rs.SOOffsets);
            }
        }
    }


    if(m_cs.RSSetState) {
        if(m_rs.RSRasterState!=m_rs_prev.RSRasterState) {
            m_super->RSSetState(m_rs.RSRasterState);
        }
    }
    if(m_cs.RSSetViewports) {
        if(m_cs.RSSetViewports) {
            if( m_rs.RSNumViewports!=m_rs_prev.RSNumViewports ||
                !equal_n(m_rs.RSViewports, m_rs.RSNumViewports, m_rs_prev.RSViewports) )
            {
                m_super->RSSetViewports(m_rs.RSNumViewports, m_rs.RSViewports);
            }
        }
    }
    if(m_cs.RSSetScissorRects) {
        if(m_cs.RSSetScissorRects) {
            if( m_rs.RSNumScissorRects!=m_rs_prev.RSNumScissorRects ||
                !equal_n(m_rs.RSScissorRects, m_rs.RSNumScissorRects, m_rs_prev.RSScissorRects) )
            {
                m_super->RSSetScissorRects(m_rs.RSNumScissorRects, m_rs.RSScissorRects);
            }
        }
    }


    m_rs_prev = m_rs; // todo: このコピーかなり重いはず。面倒だけど↑の実際の API call の際に最小限コピーすることで軽減できるはず
    m_cs = CallStates();
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
    m_cs.VSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.VSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.PSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.PSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShader( ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.PSSetShader = true;
    m_rs.PSShader = pPixelShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.PSClassInstances);
    m_rs.PSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.PSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.PSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShader( ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.VSSetShader = true;
    m_rs.VSShader = pVertexShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.VSClassInstances);
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
    m_cs.PSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.PSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetInputLayout( ID3D11InputLayout *pInputLayout )
{
    m_cs.IASetInputLayout = true;
    m_rs.IAInputLayout = pInputLayout;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetVertexBuffers(  UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppVertexBuffers, const UINT *pStrides, const UINT *pOffsets )
{
    m_cs.IASetVertexBuffers = true;
    copy_n(ppVertexBuffers, NumBuffers, m_rs.IAVertexBuffers+StartSlot);
    copy_n(pStrides, NumBuffers, m_rs.IAVertexBufferStrides+StartSlot);
    copy_n(pOffsets, NumBuffers, m_rs.IAVertexBufferOffsets+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetIndexBuffer(  ID3D11Buffer *pIndexBuffer, DXGI_FORMAT Format, UINT Offset )
{
    m_cs.IASetIndexBuffer = true;
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
    m_cs.GSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.GSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetShader( ID3D11GeometryShader *pShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.GSSetShader = true;
    m_rs.GSShader = pShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.GSClassInstances);
    m_rs.GSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY Topology )
{
    m_cs.IASetPrimitiveTopology = true;
    m_rs.IAPrimitiveTopology = Topology;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.VSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.VSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.VSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.VSSamplers+StartSlot);
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
    m_cs.GSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.GSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.GSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.GSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargets( UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView)
{
    m_cs.OMSetRenderTargets = true;
    m_rs.OMNumRenderTargets = NumViews;
    copy_n(ppRenderTargetViews, NumViews, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(  UINT NumRTVs, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts)
{
    m_cs.OMSetRenderTargetsAndUnorderedAccessViews = true;
    m_rs.OMNumRenderTargets = NumRTVs;
    copy_n(ppRenderTargetViews, NumRTVs, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;
    copy_n(ppUnorderedAccessViews, NumUAVs, m_rs.OMUnorderedAccesses+UAVStartSlot);
    copy_n(pUAVInitialCounts, NumUAVs, m_rs.OMUnorderedInitialCounts+UAVStartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetBlendState( ID3D11BlendState *pBlendState, const FLOAT BlendFactor[ 4 ], UINT SampleMask )
{
    m_cs.OMSetBlendState = true;
    m_rs.OMBlendState = pBlendState;
    copy_n(BlendFactor, _countof(m_rs.OMBlendFactor), m_rs.OMBlendFactor);
    m_rs.OMBlendSampleMask = SampleMask;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetDepthStencilState( ID3D11DepthStencilState *pDepthStencilState, UINT StencilRef )
{
    m_cs.OMSetDepthStencilState = true;
    m_rs.OMDepthStencilState = pDepthStencilState;
    m_rs.OMStencilRef = StencilRef;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOSetTargets( UINT NumBuffers, ID3D11Buffer *const *ppSOTargets, const UINT *pOffsets )
{
    m_cs.SOSetTargets = true;
    copy_n(ppSOTargets, NumBuffers, m_rs.SOTargets);
    copy_n(pOffsets, NumBuffers, m_rs.SOOffsets);
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
    m_cs.RSSetState = true;
    m_super->RSSetState(pRasterizerState);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSSetViewports( UINT NumViewports, const D3D11_VIEWPORT *pViewports )
{
    m_cs.RSSetViewports = true;
    m_rs.RSNumViewports = NumViewports;
    copy_n(pViewports, NumViewports, m_rs.RSViewports);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSSetScissorRects( UINT NumRects, const D3D11_RECT *pRects )
{
    m_cs.RSSetScissorRects = true;
    m_rs.RSNumScissorRects = NumRects;
    copy_n(pRects, NumRects, m_rs.RSScissorRects);
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
    m_cs.HSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.HSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetShader( ID3D11HullShader *pHullShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.HSSetShader = true;
    m_rs.HSShader = pHullShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.HSClassInstances);
    m_rs.HSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.HSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.HSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.HSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.HSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.DSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.DSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShader( ID3D11DomainShader *pDomainShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.DSSetShader = true;
    m_rs.DSShader = pDomainShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.DSClassInstances);
    m_rs.DSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.DSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.DSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.DSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.DSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.CSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.CSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts )
{
    m_cs.CSSetUnorderedAccessViews = true;
    copy_n(ppUnorderedAccessViews, NumUAVs, m_rs.CSUnorderedAccesses+StartSlot);
    copy_n(pUAVInitialCounts, NumUAVs, m_rs.CSUnorderedInitialCounts+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShader( ID3D11ComputeShader *pComputeShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.CSSetShader = true;
    m_rs.CSShader = pComputeShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.CSClassInstances);
    m_rs.CSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.CSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.CSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.CSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.CSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.VSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    addref_and_copy_n(m_rs.PSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShader( ID3D11PixelShader **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.PSShader, 1, ppPixelShader);
    addref_and_copy_n(m_rs.PSClassInstances, _countof(m_rs.PSClassInstances), ppClassInstances);
    *pNumClassInstances = m_rs.PSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.PSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShader( ID3D11VertexShader **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.VSShader, 1, ppVertexShader);
    addref_and_copy_n(m_rs.VSClassInstances, _countof(m_rs.VSClassInstances), ppClassInstances);
    *pNumClassInstances = m_rs.VSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.PSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetInputLayout( ID3D11InputLayout **ppInputLayout )
{
    addref_and_copy_n(&m_rs.IAInputLayout, 1, ppInputLayout);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetVertexBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppVertexBuffers, UINT *pStrides, UINT *pOffsets )
{
    addref_and_copy_n(m_rs.IAVertexBuffers+StartSlot, NumBuffers, ppVertexBuffers);
    copy_n(m_rs.IAVertexBufferStrides+StartSlot, NumBuffers, pStrides);
    copy_n(m_rs.IAVertexBufferOffsets+StartSlot, NumBuffers, pOffsets);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetIndexBuffer( ID3D11Buffer **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset )
{
    addref_and_copy_n(&m_rs.IAIndexBuffer, 1, pIndexBuffer);
    *Format = m_rs.IAIndexBufferFormat;
    *Offset = m_rs.IAIndexBufferOffset;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.GSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShader( ID3D11GeometryShader **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.GSShader, 1, ppGeometryShader);
    addref_and_copy_n(m_rs.GSClassInstances, m_rs.GSNumClassInstances, ppClassInstances);
    *pNumClassInstances = m_rs.GSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY *pTopology )
{
    *pTopology = m_rs.IAPrimitiveTopology;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    addref_and_copy_n(m_rs.VSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.VSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GetPredication( ID3D11Predicate **ppPredicate, BOOL *pPredicateValue )
{
    m_super->GetPredication(ppPredicate, pPredicateValue);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    addref_and_copy_n(m_rs.GSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.GSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargets( UINT NumViews, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView )
{
    addref_and_copy_n(m_rs.OMRenderTargets, NumViews, ppRenderTargetViews);
    addref_and_copy_n(&m_rs.OMDepthStencil, 1, ppDepthStencilView);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews( UINT NumRTVs, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    OMGetRenderTargets(NumRTVs, ppRenderTargetViews, ppDepthStencilView);
    CSGetUnorderedAccessViews(UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetBlendState( ID3D11BlendState **ppBlendState, FLOAT BlendFactor[ 4 ], UINT *pSampleMask )
{
    addref_and_copy_n(&m_rs.OMBlendState, 1, ppBlendState);
    copy_n(m_rs.OMBlendFactor, _countof(m_rs.OMBlendFactor), BlendFactor);
    *pSampleMask = m_rs.OMBlendSampleMask;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetDepthStencilState( ID3D11DepthStencilState **ppDepthStencilState, UINT *pStencilRef )
{
    addref_and_copy_n(&m_rs.OMDepthStencilState, 1, ppDepthStencilState);
    *pStencilRef = m_rs.OMStencilRef;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOGetTargets( UINT NumBuffers, ID3D11Buffer **ppSOTargets )
{
    addref_and_copy_n(m_rs.SOTargets, NumBuffers, ppSOTargets);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetState( ID3D11RasterizerState **ppRasterizerState )
{
    addref_and_copy_n(&m_rs.RSRasterState, 1, ppRasterizerState);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetViewports( 
    UINT *pNumViewports,
    D3D11_VIEWPORT *pViewports)
{
    *pNumViewports = m_rs.RSNumViewports;
    copy_n(m_rs.RSViewports, m_rs.RSNumViewports, pViewports);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetScissorRects( UINT *pNumRects, D3D11_RECT *pRects )
{
    *pNumRects = m_rs.RSNumScissorRects;
    copy_n(m_rs.RSScissorRects, m_rs.RSNumScissorRects, pRects);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShaderResources( 
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView **ppShaderResourceViews)
{
    addref_and_copy_n(m_rs.HSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShader( ID3D11HullShader **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.HSShader, 1, ppHullShader);
    addref_and_copy_n(m_rs.HSClassInstances, m_rs.HSNumClassInstances, ppClassInstances);
    *pNumClassInstances = m_rs.HSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.HSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.HSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    addref_and_copy_n(m_rs.DSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShader( ID3D11DomainShader **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.DSShader, 1, ppDomainShader);
    addref_and_copy_n(m_rs.DSClassInstances, m_rs.DSNumClassInstances, ppClassInstances);
    *pNumClassInstances = m_rs.DSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.DSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.DSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    addref_and_copy_n(m_rs.CSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    addref_and_copy_n(m_rs.CSUnorderedAccesses+StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShader( ID3D11ComputeShader **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    addref_and_copy_n(&m_rs.CSShader, 1, ppComputeShader);
    addref_and_copy_n(m_rs.CSClassInstances, m_rs.CSNumClassInstances, ppClassInstances);
    *pNumClassInstances = m_rs.CSNumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    addref_and_copy_n(m_rs.CSSamplers+StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    addref_and_copy_n(m_rs.CSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
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
