// �ͻ���

#include <Pigeon.h>

class Sandbox : public Pigeon::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

// ����Ӧ�ó���Ĳ��ֽ��������ȥʵ��
Pigeon::Application* Pigeon::CreateApplication()
{
	return new Sandbox();
}
