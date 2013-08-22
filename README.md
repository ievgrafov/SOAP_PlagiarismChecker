shingleServerSOAP
=================

HOWTO install

I. Application itself

1) git clone https://github.com/dilcom/shingleServerSOAP.git

2) cd ./shinglsAlg/projects/QMAKE

3) qmake & make if you have installed libqt-devel
   or
   build in qtcreator
   
Done!

II. Redis Cluster

1) git clone https://github.com/antirez/redis.git

2) cd ./redis/

3) cluster meet didn`t work for me without that small fix https://github.com/antirez/redis/pull/1196

4) make

5.0) configure it (readme here https://github.com/antirez/redis), enable cluster mode and choose a port

5.1) my config here http://db.tt/vRSLkKCJ - only 1 node, if you need more, copy it and replace 6379 -> any_port

5.2) build hiredis

  5.2.1) cd ./deps/hiredis
  
  5.2.2) make & make install  ! or use checkinstall or something like that

6) ./src/redis-server configFileName.conf
    each node have its own *.conf file, I used at least 3 nodes (to let masters choose slaves on crashed masters place)

7) ./src/redis-trib.rb create ip.address.node1:port1 ip.address.node2:port2 ... ip.address.nodeN:portN 
   it creates cluster of N nodes, all of them must be running

Done!
