package valasztas;

import java.util.HashMap;
import java.util.Map;

public class HashVoteSystem<T> implements VoteSystem<T> {
    private final HashMap<T, Parties> votes;
    public boolean voteInProgess;

    public HashVoteSystem() {
        voteInProgess = true;
        this.votes = new HashMap<>();
    }

    @Override
    public void vote(Authorizable<T> voter, Parties party) {
        if (voteInProgess) {
            if (!votes.containsKey(voter.getKey())) {
                votes.put(voter.getKey(), party);
            } else {
                throw new AlreadyVoted(voter.getKey().toString());
            }
        } else {
            throw new IllegalStateException("Vote is already over!");
        }
    }

    @Override
    public long getCountFor(Parties party) {
        if (voteInProgess) {
            throw new IllegalStateException("Vote is still going!");
        }
        int count = 0;
        for (Map.Entry<T, Parties> entry : votes.entrySet()) {
            if (entry.getValue() == party) {
                ++count;
            }
        }
        return count;
    }

    @Override
    public void closeVoting() {
        voteInProgess = false;
    }

    @Override
    public int getVoteCount(){
        return votes.size();
    }

    @Override
    public Parties getWinner() {
        if (voteInProgess) {
            throw new IllegalStateException("Vote is still going!");
        }
        long cppCount = getCountFor(Parties.CPP_FANS);
        long javaCount = getCountFor(Parties.JAVA_HEROES);
        long haskellCount = getCountFor(Parties.HASKELL_MAGES);

        long winner = Math.max(cppCount, Math.max(javaCount, haskellCount));
        if (winner == cppCount) {
            return Parties.CPP_FANS;
        } else if (winner == javaCount) {
            return Parties.JAVA_HEROES;
        } else if (winner == haskellCount) {
            return Parties.HASKELL_MAGES;
        } else {
            throw new IllegalStateException("We don't have any valid votes!");
        }
    }
}