A=read.table("data.txt");
postscript("spr.eps")
plot(A$V1,A$V2*(180/3.141592),type="l",xlab="Internal angle", ylab="Rpp")
dev.off()

