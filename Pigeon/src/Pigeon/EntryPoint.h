#pragma once


#ifdef PG_PLATFORM_WINDOWS

extern Pigeon::Application* Pigeon::CreateApplication();	//�ͻ���ʵ�֣���Application.h�ж���

int main(int argc, char** argv)
{
	auto app = Pigeon::CreateApplication();	//����Ӧ�ó���
	app->Run();
	delete app;
}

#endif