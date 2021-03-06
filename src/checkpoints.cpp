// Copyright (c) 2009-2012 The OFIChain developers
// Copyright (c) 2011-2017 The OFIChain developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "db.h"
#include "main.h"
#include "txdb.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;   // hardened checkpoints

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockOfficial )//<ZXB>
         ( 10000, uint256("0x000000125c1baef7667ddb30bdbe3d2be8e9bf4392622669c2e744206d56bee7"))
         ( 30000, uint256("0x0000000b8893493dace740437e7d606a66c7af4aa2cdfc438a9b351af3a6d218"))   
       	( 53168, uint256("0x0000002f128e8d1e2498477d7e75fb7bd552c7f6bbcf54537351c534a0819a46"))
    	( 53169, uint256("0x0000000e0162b2a9bd101230828bb2a6d8ffae11722190c0d67ab1afea42c6da"))
    	( 53170, uint256("0x4e28ac02eef4af810ad1d94e4eef8ae345ed10ed7e5f8b21a25231dc7e09f635"))
    	( 54004, uint256("0x00000013b30a3909494ffc6f00fdfbfb5006f80662d834fd5f03f9a6aef2d7c4"))
    	( 54005, uint256("0x0000001a564560a4fe58dc70dd2ff56d4c4665bc5d273952d554d240d1d7008b"))
    	( 54322, uint256("0x000000068494cee59e7b0f41037ed6f42e0312dc1c949f495f084d2dd0d202a4"))
    	( 54323, uint256("0x0000001e9caa5dd09b706f24060be7c26405b752b3b36c23a2a31f591aaca296"))

        // ( 99999, uint256("0x27fd5e1de16a4270eb8c68dee2754a64da6312c7c3a0e99a7e6776246be1ee3f"))
        // (219999, uint256("0xab0dad4b10d2370f009ed6df6effca1ba42f01d5070d6b30afeedf6463fbe7a2"))
        // (336000, uint256("0x4d261cef6e61a5ed8325e560f1d6e36f4698853a4c7134677f47a1d1d842bdf6"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1511962881, // * UNIX timestamp of last checkpoint block
        1331659,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        1000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1338180505,
        16341,
        300
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    uint256 GetLatestHardenedCheckpoint()
    {
        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;
        return (checkpoints.rbegin()->second);
    }
}
