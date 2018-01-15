package pingpong;

import hu.elte.txtuml.api.deployment.Configuration;
import hu.elte.txtuml.api.deployment.Group;
import pingpong.model.Judge;
import pingpong.model.PingPongMatch;
import pingpong.model.Player;
import pingpong.model.Table;

@Group(contains = {Player.class, PingPongMatch.class, Judge.class, Table.class})
public class PingPongConf extends Configuration {

}
