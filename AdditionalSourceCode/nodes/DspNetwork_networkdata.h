namespace project
{

struct DspNetwork_networkdata: public scriptnode::dll::InterpretedNetworkData
{
	String getId() const override
	{
		return "DspNetwork";
	}
	bool isModNode() const override
	{
		return false;
	}
	String getNetworkData() const override
	{
		return "120.nT6K8CRm8M..hb3EZ.WZa3YJmNKsVgLQNc67Tl.GBUUcEfhh1l9A+m2ryEbQj+yEWtfpmNF2SRlQlFBuwPkEZyFC6ltNCtqzHRyp8BK.3dlnp6dBkPoSf6MkwadPwvGGA2OLTbGwpI5TEP..cg.Lh1Exlvbybm2A";
	}
};
}

