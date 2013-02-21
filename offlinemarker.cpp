#include <znc/Chan.h>
#include <znc/User.h>
#include <znc/IRCNetwork.h>
#include <znc/Modules.h>

using std::vector;

class COfflineMarkerMod : public CModule {
public:
	MODCONSTRUCTOR(COfflineMarkerMod) {}
	virtual ~COfflineMarkerMod() {}

	void AddBuffer(CChan& Channel, const CString& sMessage) {
		// If they have automatic buffer clearing enabled, only add messages if no client is connected
		if (Channel.AutoClearChanBuffer() && m_pNetwork->IsUserOnline())
			return;

		Channel.AddBuffer(":" + GetModNick() + "!" + GetModName() + "@znc.in PRIVMSG " + _NAMEDFMT(Channel.GetName()) + " :{text}", sMessage);
	}

	virtual void OnClientDisconnect() {
		// Loop through all networks, and all channels/buffers. Put a "-- MARK --" into each buffer.
		const vector<CChan *>& vChans = m_pNetwork->GetChans();
		vector<CChan*>::const_iterator it;
		for (it = vChans.begin(); it != vChans.end(); ++it) {
			AddBuffer(**it, "-- MARK --");
		}
	}
};

MODULEDEFS(COfflineMarkerMod, "Put a mark in all logged buffers when client disconnects.")
