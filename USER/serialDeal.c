#include "serialDeal.h"
#include "usart1.h"

char CommandBuff[10]={0};	//������� ���������9λ ��10λ����������� Ϊffʱ���
uint8_t CommandPot=0;

void cmd_commit(void);
void s_sendData(char cdata);
uint8_t str_cmp(char *in1, char *in2, uint8_t len);


//���ڽ����жϴ��������
void s_receive(char recData){

	if(recData=='@'){	//������������� @
		//s_sendData('~');
		cmd_commit();
	}else{
		CommandBuff[CommandPot]=recData;
		//s_sendData('^');
		//s_sendData(recData);
		if(CommandPot<9){
			CommandPot++;
		}
	}
}

//���ڷ�������
void s_sendData(char cdata){
	UART1SendByte(cdata);
}

//���ڷ����ַ�������
void s_sendStr(char *sdata, uint8_t len){
	uint8_t i;
	for(i=0;i<len;i++){
		s_sendData(sdata[i]);
		if(sdata[i]==0x00){
			break;
		}
	}
}

//�����ύָ��
void cmd_commit(){
	// uint8_t tempStr[6]={0};//�����¶�ת��Ϊ�ַ���

	CommandBuff[CommandPot]=0;
	
	s_sendStr("cmd:[",7);
	s_sendStr(CommandBuff,10);
	s_sendStr("]\n",2);

	//ִ�е�ǰ������������
	if(CommandBuff[9]!='\0'){
		s_sendStr("Command Overflow!",18);
		
	}else{
		if(str_cmp(CommandBuff,"Temp",10)){
			s_sendStr("Welcome",25);
		}
	}

	//�����������
	CommandBuff[9]=0x00;
	CommandPot=0;
}

//�Ա��ַ����Ƿ�һ��
uint8_t str_cmp(char *in1, char *in2, uint8_t len){
	uint8_t i=0;
	while(in1[i]!='\0' && in2[i]!='\0' && i<len){
		if(in1[i]!=in2[i]){
			return 0;
		}
		i++;
	}
	if(in1[i]!=in2[i]){
		return 0;
	}
	return 1;
}
