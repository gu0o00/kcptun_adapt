# kcptun_adapt
kcptun与shadowsocks接口之间的适配器，来使kcptun支持shadowsocks的接口协议

## 简介
根据shadowsocks的声明，所以实现了这个kcptun的sip003接口的协议的适配器
> ### Restrictions
> a. Plugin over plugin is NOT supported. Only one plugin can be enabled when a shadowsocks service is started. If you really need this feature, implement a plugin-over-plugin transport as a SIP003 plugin. b. Only TCP traffic is forwarded. For now, there is no plan to support UDP traffic forwarding.

[SIP003: A simplified plugin design for shadowsocks](https://shadowsocks.org/en/spec/Plugin.html)

## 使用说明

- 服务器地址：正常填写
- 服务器端口：kcp的远程监听端口
- 密码：ss的密码
- 加密：ss的加密方法
- 插件：kcptun适配器的名字，我的是重命名为kcptun_adapt.exe
- 插件选项：kcptun的启动选项，其中--localaddr(-l)，--remoteaddr(-r)不需要填写，我这里是填入了mode，crypt，key三个参数。
         参数填入的格式是key1=value1;key2=value2...

![配置方法](https://github.com/DaPangR/kcptun_adapt/blob/master/configure.jpg)

> tips:目前发现使用kcptun会产生发送数据包为接收数据包3倍的情况，即在youtube看1M的视频，kcptun会让vps发送3M的数据

> tips:可以试下BBR，速度比kcptun稍慢，但不会产生流量浪费的情况。[开启TCP BBR拥塞控制算法](https://github.com/iMeiji/shadowsocks_install/wiki/%E5%BC%80%E5%90%AFTCP-BBR%E6%8B%A5%E5%A1%9E%E6%8E%A7%E5%88%B6%E7%AE%97%E6%B3%95)
