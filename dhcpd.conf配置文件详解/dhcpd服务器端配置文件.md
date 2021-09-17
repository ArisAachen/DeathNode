## 说明
dhcpd是由isc-dhcp-xxx提供的方便dhcp服务的包                
其中包含                
isc-dhcp-client      客户端                            
isc-dhcp-relay       中继               
isc-dhcp-server      服务端

## 配置说明
作为服务端主要配置文件为dhcpd.conf，配置路径是/etc/dhcp/dhcpd.conf            
主要分为      
1. parameters statement，主要负责定义行为，包括何时到期，是否分配ip给未知的客户端，是否分配网关等信息给客户端      
2. declarations 分为subnet和share，主要用于提供可分配的ip网段，如果客户端请求动态分配，则应该在subnet中指定







## 参考
https://www.net.princeton.edu/software/dhcpd/dhcpd.8.html         
