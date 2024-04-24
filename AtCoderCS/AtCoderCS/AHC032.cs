using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Procon.AtCoder
{
    class AHC032
    {
        class A_ : ILOSolver
        {
            public static TestSeed[] TestSeeds = new TestSeed[]
            {
new TestSeed(
    "9 20 81\r\n24323530 980293589 859258684 185499104 894688371 236405725 111530575 250271104 495624658\r\n769596495 264300425 88876278 146578260 565437828 737999180 725732147 57726456 323844609\r\n40096771 928203404 501627737 804865949 814572382 849529199 189832922 910184599 467494517\r\n962420139 432607222 59818053 858072870 914485919 446805915 138548911 345246064 245004268\r\n477044564 12166358 931360092 799278793 865992483 339109407 614502753 736626962 801948371\r\n281576446 640350568 771040910 823574138 350308411 930294372 585808288 700370699 426021090\r\n289960346 566527193 119082954 148354804 902944838 516738876 930961873 812731496 172242940\r\n921564237 662077279 49476329 593121834 377147282 862136854 791213996 686329230 7403815\r\n501340655 979965930 839183331 303883398 490179686 492481098 160122974 114672637 82049594\r\n975741402 918762324 476374754\r\n906657349 359110092 978536040\r\n84599745 368692094 744129488\r\n261705356 216870728 556481274\r\n317767465 457532475 532110106\r\n125703669 839188333 425571806\r\n291667039 37052662 1276219\r\n305291998 653050074 220563016\r\n332525785 400712871 520185762\r\n393148157 178758620 933441647\r\n205044518 579917402 498932315\r\n411369672 664953833 274696537\r\n654712800 802006144 682742340\r\n864455037 533661060 207561332\r\n605472509 577911453 942938903\r\n576270626 688256275 33493069\r\n481710779 902547317 817131623\r\n291465541 863597953 772086608\r\n417987422 136453150 615090472\r\n760882895 841541285 914039365\r\n359505208 780663578 774735965\r\n188919347 431579412 464452916\r\n854985721 70294202 663019966\r\n157776983 3557297 439447307\r\n621014939 759908222 932643321\r\n184225959 884108948 693640679\r\n361651737 846036661 975413204\r\n479224933 700946167 622558051\r\n495003914 325785117 513339213\r\n70238660 857642866 297571112\r\n374937799 48000646 849682071\r\n528095305 232520890 469018467\r\n952599070 610262715 232403912\r\n316958602 24859140 385411996\r\n304561106 853230688 859071983\r\n266806117 99442261 881952734\r\n708824083 752081152 915353520\r\n261135036 48934653 945657700\r\n255395109 742827901 445178710\r\n906120195 565840603 316740986\r\n736297599 447489530 680619574\r\n654670835 694926131 897183420\r\n958993686 813942152 196144122\r\n324334792 928014325 852381591\r\n194958307 642660824 128931372\r\n303306950 687790222 930130148\r\n591510740 614681348 113389792\r\n160195595 683240268 555351204\r\n218729338 196609467 724290289\r\n47413572 552092134 337674489\r\n410209863 549012244 186533965\r\n452647000 449090484 733453206\r\n106059177 888943736 940915649\r\n692940521 382797569 893532614\r\n52383100 783583840 634565824\r\n168433778 751831139 356971915\r\n870682287 872212766 75893565\r\n262231629 844472478 843213274\r\n499286296 502562654 725538734\r\n467780532 720085509 907848638\r\n",
    "4\r\n0 1 6\r\n6 6 6\r\n18 6 1\r\n16 1 5\r\n"),
            };
            string result = "";
            public override void Input()
            {
                const long mod = 998244352;
                var (N, M, K, _) = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToArray();
                var A = new List<List<long>>();
                for (int i = 0; i < N; i++)
                {
                    var a = Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToList();
                    A.Add(a);
                }
                var S = new List<List<List<long>>>();
                for (int i = 0; i < M; i++)
                {
                    var s = new List<List<long>>();
                    for (int j = 0; j < 3; j++)
                    {
                        s.Add(Console.ReadLine()!.Split().Select(v => long.Parse(v)).ToList());
                    }
                    S.Add(s);
                }
                long maxuScore = 0;
                int maxuStamp = -1;
                var uScores = new List<long>();
                for (int m = 0; m < M; m++)
                {
                    var score = 0L;
                    for (int j = 0; j < 3; j++)
                    {
                        score += S[m][0][j] % mod;
                    }
                    if (score > maxuScore)
                    {
                        maxuScore = score;
                        maxuStamp = m;
                    }
                    uScores.Add(score);
                }
                long maxlScore = 0;
                int maxlStamp = -1;
                var lScores = new List<long>();
                for (int m = 0; m < M; m++)
                {
                    var score = 0L;
                    for (int i = 0; i < 3; i++)
                    {
                        score += S[m][i][0] % mod;
                    }
                    if (score > maxlScore)
                    {
                        maxlScore = score;
                        maxlStamp = m;
                    }
                    lScores.Add(score);
                }
                long maxulScore = 0;
                int maxulStamp = -1;
                var ulScores = new List<long>();
                for (int m = 0; m < M; m++)
                {
                    long score = S[m][0][0] % mod;
                    if (score > maxulScore)
                    {
                        maxulScore = score;
                        maxulStamp = m;
                    }
                    ulScores.Add(score);
                }
                long maxtotalScore = 0;
                int maxtotalStamp = -1;
                var totalScores = new List<long>();
                for (int m = 0; m < M; m++)
                {
                    var score = lScores[m] + uScores[m] - ulScores[m];
                    for (int i = 1; i < 3; i++)
                    {
                        for (int j = 1; j < 3; j++)
                        {
                            score += S[m][i][j] % mod;
                        }
                    }
                    if (score > maxtotalScore)
                    {
                        maxtotalScore = score;
                        maxtotalStamp = m;
                    }
                    totalScores.Add(score);
                }
                var results = new List<string>
            {
                "49"
            };
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        results.Add($"{maxulStamp} {i} {j}");
                    }
                }
                for (int j = 0; j < 6; j++)
                {
                    results.Add($"{maxlStamp} {6} {j}");
                }
                for (int i = 0; i < 6; i++)
                {
                    results.Add($"{maxlStamp} {i} {6}");
                }
                results.Add($"{maxtotalStamp} {6} {6}");
                result = string.Join(Environment.NewLine, results);

            }
            public override void Solve()
            {
            }
            public override void Output()
            {
                Console.WriteLine($"{result}");
            }
        }
    }


}
