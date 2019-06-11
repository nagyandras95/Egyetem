package valasztas;

import java.util.ArrayList;
import java.util.HashSet;

public class ArrayVoteSystem<T> implements VoteSystem<T> {
    private final ArrayList<Parties> votes;
    private final HashSet<T> voters;
    public boolean voteInProgess;

    public ArrayVoteSystem() {
        voteInProgess = true;
        this.votes = new ArrayList<>();
        this.voters = new HashSet<>();
    }

    @Override
    public void vote(Authorizable<T> voter, Parties party) {
        if (voteInProgess) {
            if (!voters.contains(voter.getKey())) {
                voters.add(voter.getKey());
                votes.add(party);
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
        return votes.stream().filter(e -> e == party).count();

    }

    @Override
    public int getVoteCount() {
        return votes.size();
    }

    @Override
    public void closeVoting() {
        voteInProgess = false;
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