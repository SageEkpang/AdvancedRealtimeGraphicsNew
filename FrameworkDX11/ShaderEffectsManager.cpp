#include "ShaderEffectsManager.h"

ShaderEffectsManager::ShaderEffectsManager(ID3D11DeviceContext* context, ID3D11Device* device)
{
	m_ShaderStorageArray.clear();

	// INIT SHADER(s) / LOAD SHADER(s)
	m_ShaderNames.push_back(L"BoxBlurShader.fx");
	m_ShaderNames.push_back(L"BloomShader.fx");
	m_ShaderNames.push_back(L"GuassianBlurShader.fx");
	m_ShaderNames.push_back(L"GreyScaleShader.fx");
	m_ShaderNames.push_back(L"ChromaticAbberationShader.fx");
	m_ShaderNames.push_back(L"ImageEffectShader.fx");
	m_ShaderNames.push_back(L"SobelShader.fx");

	D3D11_INPUT_ELEMENT_DESC t_DefaultLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// NOTE: Pushes Built Shaders to the Shader Storage Array
	for (int i = 0; i < m_ShaderNames.size(); ++i)
	{
		const wchar_t* t_NameOfShader = m_ShaderNames[i];
		Shader* t_TempShader = new Shader(t_NameOfShader, t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), context, device);
		m_ShaderStorageArray.push_back(ShaderStorage(t_NameOfShader, t_TempShader, false));
	}

	m_ShaderNames.clear();
}

ShaderEffectsManager::~ShaderEffectsManager()
{
	std::vector<ShaderStorage>::iterator t_StoreItr;
	if (!m_ShaderStorageArray.empty())
	{
		for (t_StoreItr = m_ShaderStorageArray.begin(); t_StoreItr != m_ShaderStorageArray.end(); ++t_StoreItr)
		{
			delete (*t_StoreItr).shader;
		}
		m_ShaderStorageArray.clear();
	}

	ClearShaderManager();
}

// NOTE: May need to pass in the resultant scene shader resource as the first parameter
void ShaderEffectsManager::Draw(UINT width, UINT height, ID3D11DeviceContext* context, ID3D11Device* device, Mesh* quadMesh)
{
	// NOTE: Loop through Shader Effect Array
	for (UINT i = 0; i < m_ShaderStorageArray.size(); ++i)
	{
		if (m_ShaderStorageArray[i].isActive == false) { continue; }	
		m_ShaderIndexs.push_back(i);
	}

	// NOTE: Loop through Activated Shader Effects
	for (size_t i = 0; i < m_ShaderIndexs.size(); ++i)
	{
		// NOTE: Check if the Vector is Empty, if not, we can assume there is a stored shader output at the first index, we can use that as the output for the rest of the shader effects
		if (i != 0)
		{
			context->PSSetShaderResources(0, 1, m_ShaderEffectsVec[i - 1]->GetShaderResourceView());
			context->PSSetSamplers(0, 1, m_ShaderEffectsVec[i - 1]->GetSamplerState());
		}

		// NOTE: Do the Shader Effect Code
		ShaderEffect* t_TempEffect = nullptr;
		t_TempEffect = new ShaderEffect(SCREEN_WIDTH, SCREEN_HEIGHT, device);
		t_TempEffect->StartEffect(Colors::Black, context);
		{
			Shader::SetInputLayout(m_ShaderStorageArray[m_ShaderIndexs[i]].shader->GetInputLayout(), context);
			Shader::SetVertexShader(m_ShaderStorageArray[m_ShaderIndexs[i]].shader->GetVertexShader(), context);
			Shader::SetPixelShader(m_ShaderStorageArray[m_ShaderIndexs[i]].shader->GetPixelShader(), context);
			quadMesh->Draw(context);
		}
		t_TempEffect->EndEffect(context);

		// NOTE: Save the outputted Shader Effect
		m_ShaderEffectsVec.push_back(t_TempEffect);
	}
}

void ShaderEffectsManager::ClearShaderManager()
{
	// CLEAR VECTORS
	std::vector<ShaderEffect*>::iterator t_ShaderItr;
	if (!m_ShaderEffectsVec.empty())
	{
		for (t_ShaderItr = m_ShaderEffectsVec.begin(); t_ShaderItr != m_ShaderEffectsVec.end(); ++t_ShaderItr)
		{
			delete *t_ShaderItr;
		}
		m_ShaderEffectsVec.clear();
	}

	if (!m_ShaderIndexs.empty()) { m_ShaderIndexs.clear(); }
}
