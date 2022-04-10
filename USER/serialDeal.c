#include "serialDeal.h"
#include "usart1.h"

char CommandBuff[10]={0};	//命令缓存区 命令长度限制9位 第10位储存溢出数据 为ff时溢出
uint8_t CommandPot=0;

void cmd_commit(void);
void s_sendData(char cdata);
uint8_t str_cmp(char *in1, char *in2, uint8_t len);


//串口接收中断传入的数据
void s_receive(char recData){

	if(recData=='@'){	//串口命令结束符 @
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

//串口发送数据
void s_sendData(char cdata){
	UART1SendByte(cdata);
}

//串口发送字符串数据
void s_sendStr(char *sdata, uint8_t len){
	uint8_t i;
	for(i=0;i<len;i++){
		s_sendData(sdata[i]);
		if(sdata[i]==0x00){
			break;
		}
	}
}

//串口提交指令
void cmd_commit(){
	// uint8_t tempStr[6]={0};//用于温度转换为字符串

	CommandBuff[CommandPot]=0;
	
	s_sendStr("cmd:[",7);
	s_sendStr(CommandBuff,10);
	s_sendStr("]\n",2);

	//执行当前缓存区的命令
	if(CommandBuff[9]!='\0'){
		s_sendStr("Command Overflow!",18);
		
	}else{
		if(str_cmp(CommandBuff,"Temp",10)){
			s_sendStr("Welcome",25);
		}
	}

	//重置命令缓存区
	CommandBuff[9]=0x00;
	CommandPot=0;
}

//对比字符串是否一致
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
