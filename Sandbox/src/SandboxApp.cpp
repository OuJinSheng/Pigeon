// �ͻ���

#include <Pigeon.h>	// ���ӵ�Pigeon��Ŀ��������ã�

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
