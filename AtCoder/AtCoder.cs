using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;

namespace AtCoder
{
    using System.Text.RegularExpressions;
    class Program
    {
        class TestParser
        {
            public void create(string url, string encoding)
            {
                var sw = new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false };
                Console.SetOut(sw);

                WebClient wc = new WebClient();

                byte[] data = wc.DownloadData(url);

                Encoding enc = Encoding.GetEncoding(encoding);
                string html = enc.GetString(data);
                string pattern = @"<h3>入力例.*?</h3>.*?<pre>[\r\n]+(.*?)[\r\n]+</pre>.*?<h3>出力例.*?</h3>.*?<pre>[\r\n]+(.*?)[\r\n]+</pre>";
                RegexOptions opt = RegexOptions.IgnoreCase | RegexOptions.Singleline | RegexOptions.Multiline;
                Regex re = new Regex(pattern, opt);
                MatchCollection mc = re.Matches(html);
                foreach (Match m in mc)
                {
                    Console.WriteLine("ADDTEST(");
                    string[] ss = m.Groups[1].Value.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
                    foreach (string s in ss)
                    {
                        Console.WriteLine("\"{0}\\n\"", s);
                    }
                    Console.WriteLine(",");
                    ss = m.Groups[2].Value.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
                    foreach (string s in ss)
                    {
                        Console.WriteLine("\"{0}\\n\"", s);
                    }
                    Console.WriteLine(");");
                }
                Console.Out.Flush();
            }

        }
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("第一引数にURLを入れてください。");
            }
            TestParser testParser = new TestParser();
            const string encoding = "UTF-8";
            testParser.create(args[0], encoding);
        }
    }
}
