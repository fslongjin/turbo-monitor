#include "batrun.h"
#include <QProcess>
#include <QDir>
#include <QString>
#include <QDebug>
BatRun::BatRun()
{
    QString strInfo;
        QProcess p(nullptr);
        QString curPath = QDir::currentPath();//获取当前应用程序目录
        QString toolpath;
        toolpath = "";    // 当前运行路径下的文件夹（其中是需要调用的.bat
        curPath.append(toolpath);  //利用append方法在路径字符串后添加文件夹字符串
        p.setWorkingDirectory(curPath); //设置工作目录
        toolpath = "/install_audio.bat";  //要调用的脚本文件
        curPath.append(toolpath); //添加脚本文件字符串
        p.start(curPath);  //运行脚本文件
        if(p.waitForFinished()){      //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            strInfo = "完成！";
        }else{
            strInfo = "bat运行错误！";
        }

        curPath = QDir::currentPath();
        toolpath = "";    // 当前运行路径下的文件夹（其中是需要调用的.bat
        curPath.append(toolpath);  //利用append方法在路径字符串后添加文件夹字符串
        p.setWorkingDirectory(curPath); //设置工作目录
        toolpath = "/install_video.bat";  //要调用的脚本文件
        curPath.append(toolpath); //添加脚本文件字符串
        p.start(curPath);  //运行脚本文件
        if(p.waitForFinished()){      //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            strInfo = "完成！";
        }else{
            strInfo = "bat运行错误！";
        }

        curPath = QDir::currentPath();
        toolpath = "";    // 当前运行路径下的文件夹（其中是需要调用的.bat
        curPath.append(toolpath);  //利用append方法在路径字符串后添加文件夹字符串
        p.setWorkingDirectory(curPath); //设置工作目录
        toolpath = "/install_splitter.bat";  //要调用的脚本文件
        curPath.append(toolpath); //添加脚本文件字符串
        p.start(curPath);  //运行脚本文件
        if(p.waitForFinished()){      //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
            strInfo = "完成！";
        }else{
            strInfo = "bat运行错误！";
        }
}
