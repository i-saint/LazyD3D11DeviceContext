﻿#include "LazyD3D11DeviceContext.h"
#include <algorithm>

using std::fill_n;

template<class Iter1, class Iter2>
inline bool equal_n(Iter1 first1, int n, Iter2 first2)
{
    return std::equal(first1, first1+n, first2);
}

template<class Iter1, class Iter2>
inline void copy_n(Iter1 first1, int n, Iter2 first2)
{
    std::copy(first1, first1+n, first2);
}

template<class Iter1, class Iter2>
inline void addref_and_copy_n(Iter1 first1, int n, Iter2 first2)
{
    Iter1 last1 = first1 + n;
    for(Iter1 i=first1; i!=last1; ++i) {
        if(*i!=NULL) {
            (*i)->AddRef();
        }
    }
    copy_n(first1, n, first2);
}

template<class Iter1>
inline void release_n(Iter1 first1, int n)
{
    Iter1 last1 = first1 + n;
    for(Iter1 i=first1; i!=last1; ++i) {
        if(*i!=NULL) {
            (*i)->Release();
        }
    }
}

template<class T, int N>
inline int release_n(const T (&ary)[N])
{
    return release_n(ary, N);
}


template<class Iter1>
inline int count_valid_pointers(Iter1 first1, int n)
{
    int r = 0;
    Iter1 last1 = first1 + n;
    for(Iter1 i=first1; i!=last1; ++i) {
        if(*i!=NULL) {
            ++r;
        }
        else {
            break;
        }
    }
    return r;
}

template<class T, int N>
inline int count_valid_pointers(const T (&ary)[N])
{
    return count_valid_pointers(ary, N);
}


template<class Iter1>
inline int first_valid_pointer(Iter1 first1, int n)
{
    int r = 0;
    Iter1 last1 = first1 + n;
    for(Iter1 i=first1; i!=last1; ++i) {
        if(*i==NULL) {
            ++r;
        }
        else {
            break;
        }
    }
    return r;
}

template<class T, int N>
inline int first_valid_pointer(const T (&ary)[N])
{
    return first_valid_pointer(ary, N);
}



LazyD3D11DeviceContext::RenderStates::RenderStates()
{
    // no problem!
    memset(this, 0, sizeof(*this));
}
LazyD3D11DeviceContext::CallStates::CallStates()
{
    Clear();
}

void LazyD3D11DeviceContext::CallStates::Clear()
{
    // no problem!
    memset(this, 0, sizeof(*this));
}


ID3D11DeviceContext* LazyD3D11DeviceContext::Create( ID3D11DeviceContext *_super )
{
    return new LazyD3D11DeviceContext(_super);
}


void LazyD3D11DeviceContext::ActualSetRenderState()
{
    if(m_cs.PSSetShader) {
        if(m_rs.PSShader!=m_rsp.PSShader || m_rs.PSNumClassInstances!=m_rsp.PSNumClassInstances ||
            !equal_n(m_rs.PSClassInstances, m_rs.PSNumClassInstances, m_rsp.PSClassInstances) )
        {
            m_super->PSSetShader(m_rs.PSShader, m_rs.PSClassInstances, m_rs.PSNumClassInstances);
            m_rsp.PSShader = m_rs.PSShader;
            copy_n(m_rs.PSClassInstances, m_rs.PSNumClassInstances, m_rsp.PSClassInstances);
            m_rsp.PSNumClassInstances = m_rs.PSNumClassInstances;
        }
    }
    if(m_cs.VSSetShader) {
        if(m_rs.VSShader!=m_rsp.VSShader || m_rs.VSNumClassInstances!=m_rsp.VSNumClassInstances ||
            !equal_n(m_rs.VSClassInstances, m_rs.VSNumClassInstances, m_rsp.VSClassInstances) )
        {
            m_super->VSSetShader(m_rs.VSShader, m_rs.VSClassInstances, m_rs.VSNumClassInstances);
            m_rsp.VSShader = m_rs.VSShader;
            copy_n(m_rs.VSClassInstances, m_rs.VSNumClassInstances, m_rsp.VSClassInstances);
            m_rsp.VSNumClassInstances = m_rs.VSNumClassInstances;
        }
    }
    if(m_cs.GSSetShader) {
        if(m_rs.GSShader!=m_rsp.GSShader || m_rs.GSNumClassInstances!=m_rsp.GSNumClassInstances ||
            !equal_n(m_rs.GSClassInstances, m_rs.GSNumClassInstances, m_rsp.GSClassInstances) )
        {
            m_super->GSSetShader(m_rs.GSShader, m_rs.GSClassInstances, m_rs.GSNumClassInstances);
            m_rsp.GSShader = m_rs.GSShader;
            copy_n(m_rs.GSClassInstances, m_rs.GSNumClassInstances, m_rsp.GSClassInstances);
            m_rsp.GSNumClassInstances = m_rs.GSNumClassInstances;
        }
    }
    if(m_cs.HSSetShader) {
        if(m_rs.HSShader!=m_rsp.HSShader || m_rs.HSNumClassInstances!=m_rsp.HSNumClassInstances ||
            !equal_n(m_rs.HSClassInstances, m_rs.HSNumClassInstances, m_rsp.HSClassInstances) )
        {
            m_super->HSSetShader(m_rs.HSShader, m_rs.HSClassInstances, m_rs.HSNumClassInstances);
            m_rsp.HSShader = m_rs.HSShader;
            copy_n(m_rs.HSClassInstances, m_rs.HSNumClassInstances, m_rsp.HSClassInstances);
            m_rsp.HSNumClassInstances = m_rs.HSNumClassInstances;
        }
    }
    if(m_cs.DSSetShader) {
        if(m_rs.DSShader!=m_rsp.DSShader || m_rs.DSNumClassInstances!=m_rsp.DSNumClassInstances ||
            !equal_n(m_rs.DSClassInstances, m_rs.DSNumClassInstances, m_rsp.DSClassInstances) )
        {
            m_super->DSSetShader(m_rs.DSShader, m_rs.DSClassInstances, m_rs.DSNumClassInstances);
            m_rsp.DSShader = m_rs.DSShader;
            copy_n(m_rs.DSClassInstances, m_rs.DSNumClassInstances, m_rsp.DSClassInstances);
            m_rsp.DSNumClassInstances = m_rs.DSNumClassInstances;
        }
    }
    if(m_cs.CSSetShader) {
        if(m_rs.CSShader!=m_rsp.CSShader || m_rs.CSNumClassInstances!=m_rsp.CSNumClassInstances ||
            !equal_n(m_rs.CSClassInstances, m_rs.CSNumClassInstances, m_rsp.CSClassInstances) )
        {
            m_super->CSSetShader(m_rs.CSShader, m_rs.CSClassInstances, m_rs.CSNumClassInstances);
            m_rsp.CSShader = m_rs.CSShader;
            copy_n(m_rs.CSClassInstances, m_rs.CSNumClassInstances, m_rsp.CSClassInstances);
            m_rsp.CSNumClassInstances = m_rs.CSNumClassInstances;
        }
    }


    if(m_cs.OMSetRenderTargets) {
        if( m_rs.OMNumRenderTargets!=m_rsp.OMNumRenderTargets ||
            !equal_n(m_rs.OMRenderTargets, m_rs.OMNumRenderTargets, m_rsp.OMRenderTargets) ||
            m_rs.OMDepthStencil!=m_rsp.OMDepthStencil )
        {
            // RenderTarget に設定されているリソースを ShaderResource に設定しようとすると強制的に NULL にされるため、
            // ここで RenderTarget は全部 NULL にしておく。
            // もっとスマートに解決したいところだが…。
            ID3D11RenderTargetView *NullRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
            std::fill_n(NullRTVs, _countof(NullRTVs), (ID3D11RenderTargetView*)NULL);
            m_super->OMSetRenderTargets(_countof(NullRTVs), NullRTVs, NULL);
        }
    }
    if(m_cs.OMSetRenderTargetsAndUnorderedAccessViews) {
        if( m_rs.OMNumRenderTargets!=m_rsp.OMNumRenderTargets ||
            !equal_n(m_rs.OMRenderTargets, m_rs.OMNumRenderTargets, m_rsp.OMRenderTargets) ||
            m_rs.OMDepthStencil!=m_rsp.OMDepthStencil ||
            m_rs.OMOnorderedAccessStartSlot!=m_rsp.OMOnorderedAccessStartSlot ||
            m_rs.OMNumOnorderedAccess!=m_rsp.OMNumOnorderedAccess ||
            !equal_n(m_rs.OMUnorderedAccesses, m_rs.OMNumOnorderedAccess, m_rsp.OMUnorderedAccesses) ||
            !equal_n(m_rs.OMUnorderedInitialCounts, m_rs.OMNumOnorderedAccess, m_rsp.OMUnorderedInitialCounts) )
        {
            // 同上
            ID3D11RenderTargetView *NullRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
            ID3D11UnorderedAccessView *NullUAVs[D3D11_PS_CS_UAV_REGISTER_COUNT];
            UINT UAVInitialCounts[D3D11_PS_CS_UAV_REGISTER_COUNT];
            std::fill_n(NullRTVs, _countof(NullRTVs), (ID3D11RenderTargetView*)NULL);
            std::fill_n(NullUAVs, _countof(NullUAVs), (ID3D11UnorderedAccessView*)NULL);
            std::fill_n(UAVInitialCounts, _countof(UAVInitialCounts), 0);
            m_super->OMSetRenderTargetsAndUnorderedAccessViews(
                0, NullRTVs, NULL,
                0, _countof(NullUAVs), NullUAVs, UAVInitialCounts);
        }
    }
    if(m_cs.CSSetUnorderedAccessViews) {
        if( !equal_n(m_rs.CSUnorderedAccesses, _countof(m_rs.CSUnorderedAccesses), m_rsp.CSUnorderedAccesses) ||
            !equal_n(m_rs.CSUnorderedInitialCounts, _countof(m_rs.CSUnorderedInitialCounts), m_rsp.CSUnorderedInitialCounts) )
        {
            // 同上
            ID3D11UnorderedAccessView *NullUAVs[D3D11_PS_CS_UAV_REGISTER_COUNT];
            UINT UAVInitialCounts[D3D11_PS_CS_UAV_REGISTER_COUNT];
            std::fill_n(NullUAVs, _countof(NullUAVs), (ID3D11UnorderedAccessView*)NULL);
            std::fill_n(UAVInitialCounts, _countof(UAVInitialCounts), 0);
            m_super->CSSetUnorderedAccessViews(0, _countof(NullUAVs), NullUAVs, UAVInitialCounts);
        }
    }


    if(m_cs.PSSetShaderResources) {
        if(!equal_n(m_rs.PSShaderResources, _countof(m_rs.PSShaderResources), m_rsp.PSShaderResources)) {
            m_super->PSSetShaderResources(0, _countof(m_rs.PSShaderResources), m_rs.PSShaderResources);
            copy_n(m_rs.PSShaderResources, _countof(m_rs.PSShaderResources), m_rsp.PSShaderResources);
        }
    }
    if(m_cs.VSSetShaderResources) {
        if(!equal_n(m_rs.VSShaderResources, _countof(m_rs.VSShaderResources), m_rsp.VSShaderResources)) {
            m_super->VSSetShaderResources(0, _countof(m_rs.VSShaderResources), m_rs.VSShaderResources);
            copy_n(m_rs.VSShaderResources, _countof(m_rs.VSShaderResources), m_rsp.VSShaderResources);
        }
    }
    if(m_cs.GSSetShaderResources) {
        if(!equal_n(m_rs.GSShaderResources, _countof(m_rs.GSShaderResources), m_rsp.GSShaderResources)) {
            m_super->GSSetShaderResources(0, _countof(m_rs.GSShaderResources), m_rs.GSShaderResources);
            copy_n(m_rs.GSShaderResources, _countof(m_rs.GSShaderResources), m_rsp.GSShaderResources);
        }
    }
    if(m_cs.HSSetShaderResources) {
        if(!equal_n(m_rs.HSShaderResources, _countof(m_rs.HSShaderResources), m_rsp.HSShaderResources)) {
            m_super->HSSetShaderResources(0, _countof(m_rs.HSShaderResources), m_rs.HSShaderResources);
            copy_n(m_rs.HSShaderResources, _countof(m_rs.HSShaderResources), m_rsp.HSShaderResources);
        }
    }
    if(m_cs.DSSetShaderResources) {
        if(!equal_n(m_rs.DSShaderResources, _countof(m_rs.DSShaderResources), m_rsp.DSShaderResources)) {
            m_super->DSSetShaderResources(0, _countof(m_rs.DSShaderResources), m_rs.DSShaderResources);
            copy_n(m_rs.DSShaderResources, _countof(m_rs.DSShaderResources), m_rsp.DSShaderResources);
        }
    }
    if(m_cs.CSSetShaderResources) {
        if(!equal_n(m_rs.CSShaderResources, _countof(m_rs.CSShaderResources), m_rsp.CSShaderResources)) {
            m_super->CSSetShaderResources(0, _countof(m_rs.CSShaderResources), m_rs.CSShaderResources);
            copy_n(m_rs.CSShaderResources, _countof(m_rs.CSShaderResources), m_rsp.CSShaderResources);
        }
    }


    if(m_cs.PSSetConstantBuffers) {
        if(!equal_n(m_rs.PSConstantBuffers, _countof(m_rs.PSConstantBuffers), m_rsp.PSConstantBuffers)) {
            m_super->PSSetConstantBuffers(0, _countof(m_rs.PSConstantBuffers), m_rs.PSConstantBuffers);
            copy_n(m_rs.PSConstantBuffers, _countof(m_rs.PSConstantBuffers), m_rsp.PSConstantBuffers);
        }
    }
    if(m_cs.VSSetConstantBuffers) {
        if(!equal_n(m_rs.VSConstantBuffers, _countof(m_rs.VSConstantBuffers), m_rsp.VSConstantBuffers)) {
            m_super->VSSetConstantBuffers(0, _countof(m_rs.VSConstantBuffers), m_rs.VSConstantBuffers);
            copy_n(m_rs.VSConstantBuffers, _countof(m_rs.VSConstantBuffers), m_rsp.VSConstantBuffers);
        }
    }
    if(m_cs.GSSetConstantBuffers) {
        if(!equal_n(m_rs.GSConstantBuffers, _countof(m_rs.GSConstantBuffers), m_rsp.GSConstantBuffers)) {
            m_super->GSSetConstantBuffers(0, _countof(m_rs.GSConstantBuffers), m_rs.GSConstantBuffers);
            copy_n(m_rs.GSConstantBuffers, _countof(m_rs.GSConstantBuffers), m_rsp.GSConstantBuffers);
        }
    }
    if(m_cs.HSSetConstantBuffers) {
        if(!equal_n(m_rs.HSConstantBuffers, _countof(m_rs.HSConstantBuffers), m_rsp.HSConstantBuffers)) {
            m_super->HSSetConstantBuffers(0, _countof(m_rs.HSConstantBuffers), m_rs.HSConstantBuffers);
            copy_n(m_rs.HSConstantBuffers, _countof(m_rs.HSConstantBuffers), m_rsp.HSConstantBuffers);
        }
    }
    if(m_cs.DSSetConstantBuffers) {
        if(!equal_n(m_rs.DSConstantBuffers, _countof(m_rs.DSConstantBuffers), m_rsp.DSConstantBuffers)) {
            m_super->DSSetConstantBuffers(0, _countof(m_rs.DSConstantBuffers), m_rs.DSConstantBuffers);
            copy_n(m_rs.DSConstantBuffers, _countof(m_rs.DSConstantBuffers), m_rsp.DSConstantBuffers);
        }
    }
    if(m_cs.CSSetConstantBuffers) {
        if(!equal_n(m_rs.CSConstantBuffers, _countof(m_rs.CSConstantBuffers), m_rsp.CSConstantBuffers)) {
            m_super->CSSetConstantBuffers(0, _countof(m_rs.CSConstantBuffers), m_rs.CSConstantBuffers);
            copy_n(m_rs.CSConstantBuffers, _countof(m_rs.CSConstantBuffers), m_rsp.CSConstantBuffers);
        }
    }


    if(m_cs.PSSetSamplers) {
        if(!equal_n(m_rs.PSSamplers, _countof(m_rs.PSSamplers), m_rsp.PSSamplers)) {
            m_super->PSSetSamplers(0, _countof(m_rs.PSSamplers), m_rs.PSSamplers);
            copy_n(m_rs.PSSamplers, _countof(m_rs.PSSamplers), m_rsp.PSSamplers);
        }
    }
    if(m_cs.VSSetSamplers) {
        if(!equal_n(m_rs.VSSamplers, _countof(m_rs.VSSamplers), m_rsp.VSSamplers)) {
            m_super->VSSetSamplers(0, _countof(m_rs.VSSamplers), m_rs.VSSamplers);
            copy_n(m_rs.VSSamplers, _countof(m_rs.VSSamplers), m_rsp.VSSamplers);
        }
    }
    if(m_cs.GSSetSamplers) {
        if(!equal_n(m_rs.GSSamplers, _countof(m_rs.GSSamplers), m_rsp.GSSamplers)) {
            m_super->GSSetSamplers(0, _countof(m_rs.GSSamplers), m_rs.GSSamplers);
            copy_n(m_rs.GSSamplers, _countof(m_rs.GSSamplers), m_rsp.GSSamplers);
        }
    }
    if(m_cs.HSSetSamplers) {
        if(!equal_n(m_rs.HSSamplers, _countof(m_rs.HSSamplers), m_rsp.HSSamplers)) {
            m_super->HSSetSamplers(0, _countof(m_rs.HSSamplers), m_rs.HSSamplers);
            copy_n(m_rs.HSSamplers, _countof(m_rs.HSSamplers), m_rsp.HSSamplers);
        }
    }
    if(m_cs.DSSetSamplers) {
        if(!equal_n(m_rs.DSSamplers, _countof(m_rs.DSSamplers), m_rsp.DSSamplers)) {
            m_super->DSSetSamplers(0, _countof(m_rs.DSSamplers), m_rs.DSSamplers);
            copy_n(m_rs.DSSamplers, _countof(m_rs.DSSamplers), m_rsp.DSSamplers);
        }
    }
    if(m_cs.CSSetSamplers) {
        if(!equal_n(m_rs.CSSamplers, _countof(m_rs.CSSamplers), m_rsp.CSSamplers)) {
            m_super->CSSetSamplers(0, _countof(m_rs.CSSamplers), m_rs.CSSamplers);
            copy_n(m_rs.CSSamplers, _countof(m_rs.CSSamplers), m_rsp.CSSamplers);
        }
    }


    if(m_cs.CSSetUnorderedAccessViews) {
        if( !equal_n(m_rs.CSUnorderedAccesses, _countof(m_rs.CSUnorderedAccesses), m_rsp.CSUnorderedAccesses) ||
            !equal_n(m_rs.CSUnorderedInitialCounts, _countof(m_rs.CSUnorderedInitialCounts), m_rsp.CSUnorderedInitialCounts) )
        {
            m_super->CSSetUnorderedAccessViews(0, _countof(m_rs.CSUnorderedAccesses), m_rs.CSUnorderedAccesses, m_rs.CSUnorderedInitialCounts);
            copy_n(m_rs.CSUnorderedAccesses, _countof(m_rs.CSUnorderedAccesses), m_rsp.CSUnorderedAccesses);
            copy_n(m_rs.CSUnorderedInitialCounts, _countof(m_rs.CSUnorderedInitialCounts), m_rsp.CSUnorderedInitialCounts);
        }
    }


    if(m_cs.IASetInputLayout) {
        if(m_rs.IAInputLayout!=m_rsp.IAInputLayout) {
            m_super->IASetInputLayout(m_rs.IAInputLayout);
            m_rsp.IAInputLayout = m_rs.IAInputLayout;
        }
    }
    if(m_cs.IASetVertexBuffers) {
        if( !equal_n(m_rs.IAVertexBuffers, _countof(m_rs.IAVertexBuffers), m_rsp.IAVertexBuffers) ||
            !equal_n(m_rs.IAVertexBufferStrides, _countof(m_rs.IAVertexBufferStrides), m_rsp.IAVertexBufferStrides) ||
            !equal_n(m_rs.IAVertexBufferOffsets, _countof(m_rs.IAVertexBufferOffsets), m_rsp.IAVertexBufferOffsets) )
        {
            m_super->IASetVertexBuffers(0, _countof(m_rs.IAVertexBuffers), m_rs.IAVertexBuffers, m_rs.IAVertexBufferStrides, m_rs.IAVertexBufferOffsets);
            copy_n(m_rs.IAVertexBuffers, _countof(m_rs.IAVertexBuffers), m_rsp.IAVertexBuffers);
            copy_n(m_rs.IAVertexBufferStrides, _countof(m_rs.IAVertexBufferStrides), m_rsp.IAVertexBufferStrides);
            copy_n(m_rs.IAVertexBufferOffsets, _countof(m_rs.IAVertexBufferOffsets), m_rsp.IAVertexBufferOffsets);
        }
    }
    if(m_cs.IASetIndexBuffer) {
        if( m_rs.IAIndexBuffer!=m_rsp.IAIndexBuffer ||
            m_rs.IAIndexBufferFormat!=m_rsp.IAIndexBufferFormat ||
            m_rs.IAIndexBufferOffset!=m_rsp.IAIndexBufferOffset )
        {
            m_super->IASetIndexBuffer(m_rs.IAIndexBuffer, m_rs.IAIndexBufferFormat, m_rs.IAIndexBufferOffset);
            m_rsp.IAIndexBuffer = m_rs.IAIndexBuffer;
            m_rsp.IAIndexBufferFormat = m_rs.IAIndexBufferFormat;
            m_rsp.IAIndexBufferOffset = m_rs.IAIndexBufferOffset;
        }
    }
    if(m_cs.IASetPrimitiveTopology) {
        if(m_rs.IAPrimitiveTopology!=m_rsp.IAPrimitiveTopology)
        {
            m_super->IASetPrimitiveTopology(m_rs.IAPrimitiveTopology);
            m_rsp.IAPrimitiveTopology = m_rs.IAPrimitiveTopology;
        }
    }


    if(m_cs.OMSetRenderTargets) {
        if( m_rs.OMNumRenderTargets!=m_rsp.OMNumRenderTargets ||
            !equal_n(m_rs.OMRenderTargets, m_rs.OMNumRenderTargets, m_rsp.OMRenderTargets) ||
            m_rs.OMDepthStencil!=m_rsp.OMDepthStencil )
        {
            m_super->OMSetRenderTargets(m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil);
            m_rsp.OMNumRenderTargets = m_rs.OMNumRenderTargets;
            copy_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets), m_rsp.OMRenderTargets);
            m_rsp.OMDepthStencil = m_rs.OMDepthStencil;
        }
    }
    if(m_cs.OMSetRenderTargetsAndUnorderedAccessViews) {
        if( m_rs.OMNumRenderTargets!=m_rsp.OMNumRenderTargets ||
            !equal_n(m_rs.OMRenderTargets, m_rs.OMNumRenderTargets, m_rsp.OMRenderTargets) ||
            m_rs.OMDepthStencil!=m_rsp.OMDepthStencil ||
            m_rs.OMOnorderedAccessStartSlot!=m_rsp.OMOnorderedAccessStartSlot ||
            m_rs.OMNumOnorderedAccess!=m_rsp.OMNumOnorderedAccess ||
            !equal_n(m_rs.OMUnorderedAccesses, m_rs.OMNumOnorderedAccess, m_rsp.OMUnorderedAccesses) ||
            !equal_n(m_rs.OMUnorderedInitialCounts, m_rs.OMNumOnorderedAccess, m_rsp.OMUnorderedInitialCounts) )
        {
            m_super->OMSetRenderTargetsAndUnorderedAccessViews(
                m_rs.OMNumRenderTargets, m_rs.OMRenderTargets, m_rs.OMDepthStencil,
                m_rs.OMOnorderedAccessStartSlot, m_rs.OMNumOnorderedAccess, m_rs.OMUnorderedAccesses, m_rs.OMUnorderedInitialCounts);
            m_rsp.OMNumRenderTargets = m_rs.OMNumRenderTargets;
            copy_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets), m_rsp.OMRenderTargets);
            m_rsp.OMDepthStencil = m_rs.OMDepthStencil;
            m_rsp.OMOnorderedAccessStartSlot = m_rs.OMOnorderedAccessStartSlot;
            m_rsp.OMNumOnorderedAccess = m_rs.OMNumOnorderedAccess;
            copy_n(m_rs.OMUnorderedAccesses, _countof(m_rs.OMUnorderedAccesses), m_rsp.OMUnorderedAccesses);
            copy_n(m_rs.OMUnorderedInitialCounts, _countof(m_rs.OMUnorderedInitialCounts), m_rsp.OMUnorderedInitialCounts);
        }
    }
    if(m_cs.OMSetBlendState) {
        if( m_rs.OMBlendState!=m_rsp.OMBlendState ||
            !equal_n(m_rs.OMBlendFactor, _countof(m_rs.OMBlendFactor), m_rsp.OMBlendFactor) ||
            m_rs.OMBlendSampleMask!=m_rsp.OMBlendSampleMask)
        {
            m_super->OMSetBlendState(m_rs.OMBlendState, m_rs.OMBlendFactor, m_rs.OMBlendSampleMask);
            m_rsp.OMBlendState = m_rs.OMBlendState;
            copy_n(m_rs.OMBlendFactor, _countof(m_rs.OMBlendFactor), m_rsp.OMBlendFactor);
            m_rsp.OMBlendSampleMask = m_rs.OMBlendSampleMask;
        }
    }
    if(m_cs.OMSetDepthStencilState) {
        if(m_rs.OMDepthStencilState!=m_rsp.OMDepthStencilState ||
            m_rs.OMStencilRef!=m_rsp.OMStencilRef)
        {
            m_super->OMSetDepthStencilState(m_rs.OMDepthStencilState, m_rs.OMStencilRef);
            m_rsp.OMDepthStencilState = m_rs.OMDepthStencilState;
            m_rsp.OMStencilRef = m_rs.OMStencilRef;
        }
    }


    if(m_cs.SOSetTargets) {
        if( !equal_n(m_rs.SOTargets, _countof(m_rs.SOTargets), m_rsp.SOTargets) ||
            !equal_n(m_rs.SOOffsets, _countof(m_rs.SOOffsets), m_rsp.SOOffsets) )
        {
            m_super->SOSetTargets(_countof(m_rs.SOTargets), m_rs.SOTargets, m_rs.SOOffsets);
            copy_n(m_rs.SOTargets, _countof(m_rs.SOTargets), m_rsp.SOTargets);
            copy_n(m_rs.SOOffsets, _countof(m_rs.SOOffsets), m_rsp.SOOffsets);
        }
    }


    if(m_cs.RSSetState) {
        if(m_rs.RSRasterState!=m_rsp.RSRasterState) {
            m_super->RSSetState(m_rs.RSRasterState);
            m_rsp.RSRasterState = m_rs.RSRasterState;
        }
    }
    if(m_cs.RSSetViewports) {
        if( m_rs.RSNumViewports!=m_rsp.RSNumViewports ||
            !equal_n(m_rs.RSViewports, m_rs.RSNumViewports, m_rsp.RSViewports) )
        {
            m_super->RSSetViewports(m_rs.RSNumViewports, m_rs.RSViewports);
            m_rsp.RSNumViewports = m_rs.RSNumViewports;
            copy_n(m_rs.RSViewports, _countof(m_rs.RSViewports), m_rsp.RSViewports);
        }
    }
    if(m_cs.RSSetScissorRects) {
        if( m_rs.RSNumScissorRects!=m_rsp.RSNumScissorRects ||
            !equal_n(m_rs.RSScissorRects, m_rs.RSNumScissorRects, m_rsp.RSScissorRects) )
        {
            m_super->RSSetScissorRects(m_rs.RSNumScissorRects, m_rs.RSScissorRects);
            m_rsp.RSNumScissorRects = m_rs.RSNumScissorRects;
            copy_n(m_rs.RSScissorRects, _countof(m_rs.RSScissorRects), m_rsp.RSScissorRects);
        }
    }


    m_cs.Clear();
}


void LazyD3D11DeviceContext::SyncToActualDeviceContext()
{
    m_super->PSGetShader(&m_rs.PSShader, m_rs.PSClassInstances, &m_rs.PSNumClassInstances);
    m_super->VSGetShader(&m_rs.VSShader, m_rs.VSClassInstances, &m_rs.VSNumClassInstances);
    m_super->GSGetShader(&m_rs.GSShader, m_rs.GSClassInstances, &m_rs.GSNumClassInstances);
    m_super->HSGetShader(&m_rs.HSShader, m_rs.HSClassInstances, &m_rs.HSNumClassInstances);
    m_super->DSGetShader(&m_rs.DSShader, m_rs.DSClassInstances, &m_rs.DSNumClassInstances);
    m_super->CSGetShader(&m_rs.CSShader, m_rs.CSClassInstances, &m_rs.CSNumClassInstances);
    release_n(&m_rs.PSShader, 1); release_n(m_rs.PSClassInstances, _countof(m_rs.PSClassInstances));
    release_n(&m_rs.VSShader, 1); release_n(m_rs.VSClassInstances, _countof(m_rs.VSClassInstances));
    release_n(&m_rs.GSShader, 1); release_n(m_rs.GSClassInstances, _countof(m_rs.GSClassInstances));
    release_n(&m_rs.HSShader, 1); release_n(m_rs.HSClassInstances, _countof(m_rs.HSClassInstances));
    release_n(&m_rs.DSShader, 1); release_n(m_rs.DSClassInstances, _countof(m_rs.DSClassInstances));
    release_n(&m_rs.CSShader, 1); release_n(m_rs.CSClassInstances, _countof(m_rs.CSClassInstances));

    m_super->PSGetShaderResources(0, _countof(m_rs.PSShaderResources), m_rs.PSShaderResources);
    m_super->VSGetShaderResources(0, _countof(m_rs.VSShaderResources), m_rs.VSShaderResources);
    m_super->GSGetShaderResources(0, _countof(m_rs.GSShaderResources), m_rs.GSShaderResources);
    m_super->HSGetShaderResources(0, _countof(m_rs.HSShaderResources), m_rs.HSShaderResources);
    m_super->DSGetShaderResources(0, _countof(m_rs.DSShaderResources), m_rs.DSShaderResources);
    m_super->CSGetShaderResources(0, _countof(m_rs.CSShaderResources), m_rs.CSShaderResources);
    release_n(m_rs.PSShaderResources, _countof(m_rs.PSShaderResources));
    release_n(m_rs.VSShaderResources, _countof(m_rs.VSShaderResources));
    release_n(m_rs.GSShaderResources, _countof(m_rs.GSShaderResources));
    release_n(m_rs.HSShaderResources, _countof(m_rs.HSShaderResources));
    release_n(m_rs.DSShaderResources, _countof(m_rs.DSShaderResources));
    release_n(m_rs.CSShaderResources, _countof(m_rs.CSShaderResources));

    m_super->PSGetConstantBuffers(0, _countof(m_rs.PSConstantBuffers), m_rs.PSConstantBuffers);
    m_super->VSGetConstantBuffers(0, _countof(m_rs.VSConstantBuffers), m_rs.VSConstantBuffers);
    m_super->GSGetConstantBuffers(0, _countof(m_rs.GSConstantBuffers), m_rs.GSConstantBuffers);
    m_super->HSGetConstantBuffers(0, _countof(m_rs.HSConstantBuffers), m_rs.HSConstantBuffers);
    m_super->DSGetConstantBuffers(0, _countof(m_rs.DSConstantBuffers), m_rs.DSConstantBuffers);
    m_super->CSGetConstantBuffers(0, _countof(m_rs.CSConstantBuffers), m_rs.CSConstantBuffers);
    release_n(m_rs.PSConstantBuffers, _countof(m_rs.PSConstantBuffers));
    release_n(m_rs.VSConstantBuffers, _countof(m_rs.VSConstantBuffers));
    release_n(m_rs.GSConstantBuffers, _countof(m_rs.GSConstantBuffers));
    release_n(m_rs.HSConstantBuffers, _countof(m_rs.HSConstantBuffers));
    release_n(m_rs.DSConstantBuffers, _countof(m_rs.DSConstantBuffers));
    release_n(m_rs.CSConstantBuffers, _countof(m_rs.CSConstantBuffers));

    m_super->PSGetSamplers(0, _countof(m_rs.PSSamplers), m_rs.PSSamplers);
    m_super->VSGetSamplers(0, _countof(m_rs.VSSamplers), m_rs.VSSamplers);
    m_super->GSGetSamplers(0, _countof(m_rs.GSSamplers), m_rs.GSSamplers);
    m_super->HSGetSamplers(0, _countof(m_rs.HSSamplers), m_rs.HSSamplers);
    m_super->DSGetSamplers(0, _countof(m_rs.DSSamplers), m_rs.DSSamplers);
    m_super->CSGetSamplers(0, _countof(m_rs.CSSamplers), m_rs.CSSamplers);
    release_n(m_rs.PSSamplers, _countof(m_rs.PSSamplers));
    release_n(m_rs.VSSamplers, _countof(m_rs.VSSamplers));
    release_n(m_rs.GSSamplers, _countof(m_rs.GSSamplers));
    release_n(m_rs.HSSamplers, _countof(m_rs.HSSamplers));
    release_n(m_rs.DSSamplers, _countof(m_rs.DSSamplers));
    release_n(m_rs.CSSamplers, _countof(m_rs.CSSamplers));

    m_super->CSGetUnorderedAccessViews(0, _countof(m_rs.CSUnorderedAccesses), m_rs.CSUnorderedAccesses);
    release_n(m_rs.CSUnorderedAccesses, _countof(m_rs.CSUnorderedAccesses));

    m_super->IAGetInputLayout(&m_rs.IAInputLayout);
    release_n(&m_rs.IAInputLayout, 1);

    m_super->IAGetVertexBuffers(0, _countof(m_rs.IAVertexBuffers), m_rs.IAVertexBuffers, m_rs.IAVertexBufferStrides, m_rs.IAVertexBufferOffsets);
    release_n(m_rs.IAVertexBuffers, _countof(m_rs.IAVertexBuffers));

    m_super->IAGetIndexBuffer(&m_rs.IAIndexBuffer, &m_rs.IAIndexBufferFormat, &m_rs.IAIndexBufferOffset);
    release_n(&m_rs.IAIndexBuffer, 1);

    m_super->IAGetPrimitiveTopology(&m_rs.IAPrimitiveTopology);

    m_super->OMGetRenderTargets(_countof(m_rs.OMRenderTargets), m_rs.OMRenderTargets, &m_rs.OMDepthStencil);
    m_rs.OMNumRenderTargets = count_valid_pointers(m_rs.OMRenderTargets);
    release_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets));
    release_n(&m_rs.OMDepthStencil, 1);

    m_super->OMGetRenderTargetsAndUnorderedAccessViews(
        _countof(m_rs.OMRenderTargets), m_rs.OMRenderTargets, &m_rs.OMDepthStencil,
        0, _countof(m_rs.OMUnorderedAccesses), m_rs.OMUnorderedAccesses);
    m_rs.OMNumRenderTargets = count_valid_pointers(m_rs.OMRenderTargets);
    m_rs.OMOnorderedAccessStartSlot = first_valid_pointer(m_rs.OMUnorderedAccesses);
    if(m_rs.OMOnorderedAccessStartSlot==_countof(m_rs.OMUnorderedAccesses)) {
        m_rs.OMOnorderedAccessStartSlot = 0;
        m_rs.OMNumOnorderedAccess = 0;
    }
    else {
        m_rs.OMNumOnorderedAccess = count_valid_pointers(m_rs.OMUnorderedAccesses+m_rs.OMOnorderedAccessStartSlot, _countof(m_rs.OMUnorderedAccesses)-m_rs.OMOnorderedAccessStartSlot);
    }
    release_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets));
    release_n(&m_rs.OMDepthStencil, 1);
    release_n(m_rs.OMUnorderedAccesses, _countof(m_rs.OMUnorderedAccesses));

    m_super->OMGetBlendState(&m_rs.OMBlendState, m_rs.OMBlendFactor, &m_rs.OMBlendSampleMask);
    release_n(&m_rs.OMBlendState, 1);

    m_super->OMGetDepthStencilState(&m_rs.OMDepthStencilState, &m_rs.OMStencilRef);
    release_n(&m_rs.OMDepthStencilState, 1);

    m_super->SOGetTargets(_countof(m_rs.SOTargets), m_rs.SOTargets);
    release_n(m_rs.SOTargets, _countof(m_rs.SOTargets));

    m_super->RSGetState(&m_rs.RSRasterState);
    release_n(&m_rs.RSRasterState, 1);

    m_super->RSGetViewports(&m_rs.RSNumViewports, m_rs.RSViewports);

    m_super->RSGetScissorRects(&m_rs.RSNumScissorRects, m_rs.RSScissorRects);

    m_rsp = m_rs;
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



void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShader( ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.PSSetShader = true;
    m_rs.PSShader = pPixelShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.PSClassInstances);
    m_rs.PSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShader( ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.VSSetShader = true;
    m_rs.VSShader = pVertexShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.VSClassInstances);
    m_rs.VSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetShader( ID3D11GeometryShader *pShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.GSSetShader = true;
    m_rs.GSShader = pShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.GSClassInstances);
    m_rs.GSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetShader( ID3D11HullShader *pHullShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.HSSetShader = true;
    m_rs.HSShader = pHullShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.HSClassInstances);
    m_rs.HSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShader( ID3D11DomainShader *pDomainShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.DSSetShader = true;
    m_rs.DSShader = pDomainShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.DSClassInstances);
    m_rs.DSNumClassInstances = NumClassInstances;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShader( ID3D11ComputeShader *pComputeShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances )
{
    m_cs.CSSetShader = true;
    m_rs.CSShader = pComputeShader;
    copy_n(ppClassInstances, NumClassInstances, m_rs.CSClassInstances);
    m_rs.CSNumClassInstances = NumClassInstances;
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.PSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.PSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.VSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.VSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.GSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.GSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.HSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.HSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.DSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.DSConstantBuffers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers )
{
    m_cs.CSSetConstantBuffers = true;
    copy_n(ppConstantBuffers, NumBuffers, m_rs.CSConstantBuffers+StartSlot);
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.PSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.PSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.VSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.VSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.GSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.GSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.HSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.HSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.DSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.DSShaderResources+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews )
{
    m_cs.CSSetShaderResources = true;
    copy_n(ppShaderResourceViews, NumViews, m_rs.CSShaderResources+StartSlot);
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.PSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.PSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.VSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.VSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.GSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.GSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.HSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.HSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.DSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.DSSamplers+StartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers )
{
    m_cs.CSSetSamplers = true;
    copy_n(ppSamplers, NumSamplers, m_rs.CSSamplers+StartSlot);
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSSetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts )
{
    m_cs.CSSetUnorderedAccessViews = true;
    copy_n(ppUnorderedAccessViews, NumUAVs, m_rs.CSUnorderedAccesses+StartSlot);
    if(pUAVInitialCounts==NULL) {
        fill_n(m_rs.CSUnorderedInitialCounts+StartSlot, NumUAVs, 0);
    }
    else {
        copy_n(pUAVInitialCounts, NumUAVs, m_rs.CSUnorderedInitialCounts+StartSlot);
    }
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

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY Topology )
{
    m_cs.IASetPrimitiveTopology = true;
    m_rs.IAPrimitiveTopology = Topology;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOSetTargets( UINT NumBuffers, ID3D11Buffer *const *ppSOTargets, const UINT *pOffsets )
{
    m_cs.SOSetTargets = true;
    copy_n(ppSOTargets, NumBuffers, m_rs.SOTargets);
    copy_n(pOffsets, NumBuffers, m_rs.SOOffsets);
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

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargets( UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView)
{
    m_cs.OMSetRenderTargets = true;
    m_rs.OMNumRenderTargets = NumViews;
    fill_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets), (ID3D11RenderTargetView*)NULL);
    copy_n(ppRenderTargetViews, NumViews, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(  UINT NumRTVs, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts)
{
    m_cs.OMSetRenderTargetsAndUnorderedAccessViews = true;
    m_rs.OMNumRenderTargets = NumRTVs;
    fill_n(m_rs.OMRenderTargets, _countof(m_rs.OMRenderTargets), (ID3D11RenderTargetView*)NULL);
    copy_n(ppRenderTargetViews, NumRTVs, m_rs.OMRenderTargets);
    m_rs.OMDepthStencil = pDepthStencilView;

    m_rs.OMOnorderedAccessStartSlot = UAVStartSlot;
    m_rs.OMNumOnorderedAccess = NumUAVs;
    fill_n(m_rs.OMUnorderedAccesses, _countof(m_rs.OMUnorderedAccesses), (ID3D11UnorderedAccessView*)NULL);
    fill_n(m_rs.OMUnorderedInitialCounts, _countof(m_rs.OMUnorderedInitialCounts), 0);
    copy_n(ppUnorderedAccessViews, NumUAVs, m_rs.OMUnorderedAccesses+UAVStartSlot);
    copy_n(pUAVInitialCounts, NumUAVs, m_rs.OMUnorderedInitialCounts+UAVStartSlot);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetBlendState( ID3D11BlendState *pBlendState, const FLOAT BlendFactor[ 4 ], UINT SampleMask )
{
    m_cs.OMSetBlendState = true;
    m_rs.OMBlendState = pBlendState;
    if(BlendFactor==NULL) {
        const FLOAT one4[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        copy_n(one4, _countof(m_rs.OMBlendFactor), m_rs.OMBlendFactor);
    }
    else {
        copy_n(BlendFactor, _countof(m_rs.OMBlendFactor), m_rs.OMBlendFactor);
    }
    m_rs.OMBlendSampleMask = SampleMask;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMSetDepthStencilState( ID3D11DepthStencilState *pDepthStencilState, UINT StencilRef )
{
    m_cs.OMSetDepthStencilState = true;
    m_rs.OMDepthStencilState = pDepthStencilState;
    m_rs.OMStencilRef = StencilRef;
}



void STDMETHODCALLTYPE LazyD3D11DeviceContext::Draw( UINT VertexCount, UINT StartVertexLocation )
{
    ActualSetRenderState();
    m_super->Draw(VertexCount, StartVertexLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawAuto( void )
{
    ActualSetRenderState();
    m_super->DrawAuto();
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexed( UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation )
{
    ActualSetRenderState();
    m_super->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawInstanced( UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation )
{
    ActualSetRenderState();
    m_super->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexedInstanced( UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation )
{
    ActualSetRenderState();
    m_super->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawIndexedInstancedIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    ActualSetRenderState();
    m_super->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DrawInstancedIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    ActualSetRenderState();
    m_super->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}


void STDMETHODCALLTYPE LazyD3D11DeviceContext::Dispatch( UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ )
{
    ActualSetRenderState();
    m_super->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DispatchIndirect( ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs )
{
    ActualSetRenderState();
    m_super->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}



HRESULT STDMETHODCALLTYPE LazyD3D11DeviceContext::Map( ID3D11Resource *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource )
{
    // Resource の Map, Copy, Update などの操作は、 *SetShaderResources() などを反映しておかないと本来と違う挙動になる可能性がある
    ActualSetRenderState();
    HRESULT r = m_super->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
    return r;
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::Unmap( ID3D11Resource *pResource, UINT Subresource )
{
    // こちらはなくてもほとんどの場合大丈夫ではあるが…
    ActualSetRenderState();
    m_super->Unmap(pResource, Subresource);
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


void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopySubresourceRegion( ID3D11Resource *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource *pSrcResource, UINT SrcSubresource, const D3D11_BOX *pSrcBox )
{
    ActualSetRenderState();
    m_super->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopyResource( ID3D11Resource *pDstResource, ID3D11Resource *pSrcResource )
{
    ActualSetRenderState();
    m_super->CopyResource(pDstResource, pSrcResource);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::UpdateSubresource( ID3D11Resource *pDstResource, UINT DstSubresource, const D3D11_BOX *pDstBox, const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch )
{
    ActualSetRenderState();
    m_super->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CopyStructureCount( ID3D11Buffer *pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView *pSrcView )
{
    ActualSetRenderState();
    m_super->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearRenderTargetView( ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[ 4 ] )
{
    ActualSetRenderState();
    m_super->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearDepthStencilView( ID3D11DepthStencilView *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil )
{
    ActualSetRenderState();
    m_super->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearUnorderedAccessViewUint( ID3D11UnorderedAccessView *pUnorderedAccessView, const UINT Values[ 4 ] )
{
    ActualSetRenderState();
    m_super->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearUnorderedAccessViewFloat( ID3D11UnorderedAccessView *pUnorderedAccessView, const FLOAT Values[ 4 ] )
{
    ActualSetRenderState();
    m_super->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
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
    ActualSetRenderState();
    m_super->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ExecuteCommandList( ID3D11CommandList *pCommandList, BOOL RestoreContextState )
{
    ActualSetRenderState();
    m_super->ExecuteCommandList(pCommandList, RestoreContextState);
    if(!RestoreContextState) {
        SyncToActualDeviceContext();
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.VSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.PSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetShader( ID3D11PixelShader **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppPixelShader != NULL) {
        addref_and_copy_n(&m_rs.PSShader, 1, ppPixelShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.PSClassInstances, _countof(m_rs.PSClassInstances), ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.PSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.PSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShader( ID3D11VertexShader **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppVertexShader != NULL) {
        addref_and_copy_n(&m_rs.VSShader, 1, ppVertexShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.VSClassInstances, _countof(m_rs.VSClassInstances), ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.VSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::PSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.PSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetInputLayout( ID3D11InputLayout **ppInputLayout )
{
    if(ppInputLayout != NULL) {
        addref_and_copy_n(&m_rs.IAInputLayout, 1, ppInputLayout);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetVertexBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppVertexBuffers, UINT *pStrides, UINT *pOffsets )
{
    if(ppVertexBuffers != NULL) {
        addref_and_copy_n(m_rs.IAVertexBuffers+StartSlot, NumBuffers, ppVertexBuffers);
    }
    if(pStrides != NULL) {
        copy_n(m_rs.IAVertexBufferStrides+StartSlot, NumBuffers, pStrides);
    }
    if(pOffsets != NULL) {
        copy_n(m_rs.IAVertexBufferOffsets+StartSlot, NumBuffers, pOffsets);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetIndexBuffer( ID3D11Buffer **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset )
{
    if(pIndexBuffer != NULL) {
        addref_and_copy_n(&m_rs.IAIndexBuffer, 1, pIndexBuffer);
    }
    if(Format != NULL) {
        *Format = m_rs.IAIndexBufferFormat;
    }
    if(Offset != NULL) {
        *Offset = m_rs.IAIndexBufferOffset;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.GSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShader( ID3D11GeometryShader **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppGeometryShader != NULL) {
        addref_and_copy_n(&m_rs.GSShader, 1, ppGeometryShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.GSClassInstances, m_rs.GSNumClassInstances, ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.GSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::IAGetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY *pTopology )
{
    if(pTopology != NULL) {
        *pTopology = m_rs.IAPrimitiveTopology;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.VSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::VSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.VSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GetPredication( ID3D11Predicate **ppPredicate, BOOL *pPredicateValue )
{
    m_super->GetPredication(ppPredicate, pPredicateValue);
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.GSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::GSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.GSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargets( UINT NumViews, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView )
{
    if(ppRenderTargetViews != NULL) {
        addref_and_copy_n(m_rs.OMRenderTargets, NumViews, ppRenderTargetViews);
    }
    if(ppDepthStencilView !=  NULL) {
        addref_and_copy_n(&m_rs.OMDepthStencil, 1, ppDepthStencilView);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews( UINT NumRTVs, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    if(ppRenderTargetViews != NULL) {
        addref_and_copy_n(m_rs.OMRenderTargets, NumRTVs, ppRenderTargetViews);
    }
    if(ppDepthStencilView !=  NULL) {
        addref_and_copy_n(&m_rs.OMDepthStencil, 1, ppDepthStencilView);
    }
    if(ppUnorderedAccessViews != NULL) {
        addref_and_copy_n(m_rs.OMUnorderedAccesses+UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetBlendState( ID3D11BlendState **ppBlendState, FLOAT BlendFactor[ 4 ], UINT *pSampleMask )
{
    if(ppBlendState != NULL) {
        addref_and_copy_n(&m_rs.OMBlendState, 1, ppBlendState);
    }
    if(BlendFactor != NULL) {
        copy_n(m_rs.OMBlendFactor, _countof(m_rs.OMBlendFactor), BlendFactor);
    }
    if(pSampleMask != NULL) {
        *pSampleMask = m_rs.OMBlendSampleMask;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::OMGetDepthStencilState( ID3D11DepthStencilState **ppDepthStencilState, UINT *pStencilRef )
{
    if(ppDepthStencilState != NULL) {
        addref_and_copy_n(&m_rs.OMDepthStencilState, 1, ppDepthStencilState);
    }
    if(pStencilRef != NULL) {
        *pStencilRef = m_rs.OMStencilRef;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::SOGetTargets( UINT NumBuffers, ID3D11Buffer **ppSOTargets )
{
    if(ppSOTargets != NULL) {
        addref_and_copy_n(m_rs.SOTargets, NumBuffers, ppSOTargets);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetState( ID3D11RasterizerState **ppRasterizerState )
{
    if(ppRasterizerState != NULL) {
        addref_and_copy_n(&m_rs.RSRasterState, 1, ppRasterizerState);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetViewports( 
    UINT *pNumViewports,
    D3D11_VIEWPORT *pViewports)
{
    if(pNumViewports != NULL) {
        *pNumViewports = m_rs.RSNumViewports;
    }
    if(pViewports != NULL) {
        copy_n(m_rs.RSViewports, m_rs.RSNumViewports, pViewports);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::RSGetScissorRects( UINT *pNumRects, D3D11_RECT *pRects )
{
    if(pNumRects != NULL) {
        *pNumRects = m_rs.RSNumScissorRects;
    }
    if(pRects != NULL) {
        copy_n(m_rs.RSScissorRects, m_rs.RSNumScissorRects, pRects);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShaderResources( 
    UINT StartSlot,
    UINT NumViews,
    ID3D11ShaderResourceView **ppShaderResourceViews)
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.HSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetShader( ID3D11HullShader **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppHullShader != NULL) {
        addref_and_copy_n(&m_rs.HSShader, 1, ppHullShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.HSClassInstances, m_rs.HSNumClassInstances, ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.HSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.HSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::HSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.HSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.DSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetShader( ID3D11DomainShader **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppDomainShader != NULL) {
        addref_and_copy_n(&m_rs.DSShader, 1, ppDomainShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.DSClassInstances, m_rs.DSNumClassInstances, ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.DSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.DSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::DSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.DSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShaderResources( UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews )
{
    if(ppShaderResourceViews != NULL) {
        addref_and_copy_n(m_rs.CSShaderResources+StartSlot, NumViews, ppShaderResourceViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetUnorderedAccessViews( UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews )
{
    if(ppUnorderedAccessViews != NULL) {
        addref_and_copy_n(m_rs.CSUnorderedAccesses+StartSlot, NumUAVs, ppUnorderedAccessViews);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetShader( ID3D11ComputeShader **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances )
{
    if(ppComputeShader != NULL) {
        addref_and_copy_n(&m_rs.CSShader, 1, ppComputeShader);
    }
    if(ppClassInstances != NULL) {
        addref_and_copy_n(m_rs.CSClassInstances, m_rs.CSNumClassInstances, ppClassInstances);
    }
    if(pNumClassInstances != NULL) {
        *pNumClassInstances = m_rs.CSNumClassInstances;
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetSamplers( UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers )
{
    if(ppSamplers != NULL) {
        addref_and_copy_n(m_rs.CSSamplers+StartSlot, NumSamplers, ppSamplers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::CSGetConstantBuffers( UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers )
{
    if(ppConstantBuffers != NULL) {
        addref_and_copy_n(m_rs.CSConstantBuffers+StartSlot, NumBuffers, ppConstantBuffers);
    }
}

void STDMETHODCALLTYPE LazyD3D11DeviceContext::ClearState( void )
{
    //m_super->ClearState();
    //SyncToActualDeviceContext();

    {
        PSSetShader(NULL, NULL, 0);
        VSSetShader(NULL, NULL, 0);
        GSSetShader(NULL, NULL, 0);
        HSSetShader(NULL, NULL, 0);
        DSSetShader(NULL, NULL, 0);
        CSSetShader(NULL, NULL, 0);
    }
    {
        ID3D11ShaderResourceView *NULLShaderResources[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
        std::fill_n(NULLShaderResources, _countof(NULLShaderResources), (ID3D11ShaderResourceView*)NULL);
        PSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
        VSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
        GSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
        HSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
        DSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
        CSSetShaderResources(0, _countof(NULLShaderResources), NULLShaderResources);
    }
    {
        ID3D11Buffer *NULLConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
        std::fill_n(NULLConstantBuffers, _countof(NULLConstantBuffers), (ID3D11Buffer*)NULL);
        PSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
        VSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
        GSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
        HSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
        DSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
        CSSetConstantBuffers(0, _countof(NULLConstantBuffers), NULLConstantBuffers);
    }
    {
        ID3D11SamplerState *NULLSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
        std::fill_n(NULLSamplers, _countof(NULLSamplers), (ID3D11SamplerState*)NULL);
        PSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
        VSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
        GSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
        HSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
        DSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
        CSSetSamplers(0, _countof(NULLSamplers), NULLSamplers);
    }
    {
        ID3D11UnorderedAccessView *NullUAVs[D3D11_PS_CS_UAV_REGISTER_COUNT];
        UINT ZeroInitialCounts[D3D11_PS_CS_UAV_REGISTER_COUNT];
        std::fill_n(NullUAVs, _countof(NullUAVs), (ID3D11UnorderedAccessView*)NULL);
        std::fill_n(ZeroInitialCounts, _countof(ZeroInitialCounts), 0);
        CSSetUnorderedAccessViews(0, _countof(NullUAVs), NullUAVs, ZeroInitialCounts);
    }
    {
        ID3D11Buffer *NullTargets[D3D11_SO_BUFFER_SLOT_COUNT];
        UINT ZeroOffsets[D3D11_SO_BUFFER_SLOT_COUNT];
        std::fill_n(NullTargets, _countof(NullTargets), (ID3D11Buffer*)NULL);
        std::fill_n(ZeroOffsets, _countof(ZeroOffsets), 0);
        SOSetTargets(_countof(NullTargets), NullTargets, ZeroOffsets);
    }

    {
        ID3D11Buffer *NullBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        UINT ZeroStrides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        UINT ZeroOffsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
        std::fill_n(NullBuffers, _countof(NullBuffers), (ID3D11Buffer*)NULL);
        std::fill_n(ZeroStrides, _countof(ZeroStrides), 0);
        std::fill_n(ZeroOffsets, _countof(ZeroOffsets), 0);
        IASetVertexBuffers(0, _countof(NullBuffers), NullBuffers, ZeroStrides, ZeroOffsets);
    }
    IASetInputLayout(NULL);
    IASetIndexBuffer(NULL, DXGI_FORMAT_UNKNOWN, 0);
    IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

    {
        ID3D11RenderTargetView *NullRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        std::fill_n(NullRTVs, _countof(NullRTVs), (ID3D11RenderTargetView*)NULL);
        OMSetRenderTargets(_countof(NullRTVs), NullRTVs, NULL);
    }
    OMSetBlendState(NULL, NULL, 0xffffffff);
    OMSetDepthStencilState(NULL, 0);

    RSSetScissorRects(0, NULL);
    RSSetViewports(0, NULL);
    RSSetState(NULL);
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
