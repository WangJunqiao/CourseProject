#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>
//tcp传输数据,消息类型协议
//注册,传一个UserInfo结构过来

#define OJ_LOG 1
#define OJ_DEBUG 1

const int MSG_TYPE_REGISTER                      =     1; //注册
const int MSG_TYPE_REGISTER_FAIL                 =     11; //注册失败,用户名被占用
const int MSG_TYPE_REGISTER_SUC                  =     12; //注册成功

//登陆,传一个UserInfo结构
const int MSG_TYPE_LOGIN                         =     2; //登陆
const int MSG_TYPE_LOGIN_SUC                     =     9; //登陆成功,server => client
const int MSG_TYPE_LOGIN_FAIL                    =     10; //登陆失败,用户名或密码错误

//聊天,传一个内容字符串
const int MSG_TYPE_CHAT                          =     3; //聊天内容
//显示,传一个要显示的内容字符串
const int MSG_TYPE_SHOWMSG                       =     4; //显示一个对话框,告诉用户一些东西
//提交代码, 题号+代码
const int MSG_TYPE_CODE                          =     5; //提交代码
//新用户登陆, 一个userInfo结构体
const int MSG_TYPE_USERLOGIN                     =     6; //新用户登陆
//在线用户注销, 一个userInfo结构体
const int MSG_TYPE_USERLOGOFF                    =     7; //用户注销
//客户端和服务器之间的握手信号,比如服务器告诉客户端是否已经成功连接到服务器
const int MSG_TYPE_CONFIRM                       =     8; //握手信号

const int MSG_TYPE_GET_PROB                      =     16; //题目列表信息
const int MSG_TYPE_PROB_DES                      =     17; //题目描述信息


const int JUDGE_RES_AC                           =     18;
const int JUDGE_RES_WA                           =     19;
const int JUDGE_RES_MLE                          =     20;
const int JUDGE_RES_CE                           =     21;
const int JUDGE_RES_TLE                          =     22;
const int JUDGE_RES_INT_ERR                      =     23; //内部错误
const int JUDGE_RES_PE                           =     24;
const int JUDGE_RES_RE                           =     25;
const int JUDGE_RES_OLE                          =     26;



const int MAX_USER_NAME_LEN                      =     15; //最长用户名长度
const int MAX_PASSWORD_LEN                       =     15; //密码最长

const quint16 HOSTPORT                           =     8899;
#endif // CONSTDATA_H
