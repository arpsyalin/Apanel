namespace APanel
{
	class AndroidPing
	{
	public:
		AndroidPing(struct icmp* picmp);
		AndroidPing();
		~AndroidPing();
		bool send_icmp(void);
		bool recv_icmp(void);
		bool unpack(char *buf,int len);
	private:
		struct icmp* micmp;
		pid_t pid;
		char* msenddata;
		char* mrecvdata;
		int mfd;
		struct sockaddr_in mgoto_addr;
		struct sockaddr_in mfrom_addr;
		int fromlen,n;
		struct protoent *protocol;

	};
}
