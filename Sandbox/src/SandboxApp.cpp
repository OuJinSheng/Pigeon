// �ͻ���

#include <Pigeon.h>	// ���ӵ�Pigeon��Ŀ��������ã�

class ExampleLayer : public Pigeon::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		PG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Pigeon::Event& event) override
	{
		PG_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Pigeon::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

// ����Ӧ�ó���Ĳ��ֽ��������ȥʵ��
Pigeon::Application* Pigeon::CreateApplication()
{
	return new Sandbox();
}
