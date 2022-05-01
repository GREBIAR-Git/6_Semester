namespace Library2
{
    public class Test
    {
        string FileName(string path)
        {
            return path.Split('\\')[^-1];
        }
    }
}