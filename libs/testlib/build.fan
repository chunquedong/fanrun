using build
class Build : build::BuildPod
{
  new make()
  {
    podName = "testlib"
    summary = ""
    srcDirs = [`fan/`]
    depends = ["sys 1.0"]
  }
}