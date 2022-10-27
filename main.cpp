#include <QDir>
#include <thread>
#include <chrono>
#include <QString>
#include <QProcess>
#include <QDirIterator>
#include <QCoreApplication>

int startToolbox()
{
    QString noggit(QDir::currentPath() + "/noggit.exe");
    if (!QFileInfo::exists(noggit))
        return 1;

    QProcess process;
    process.setProgram(noggit);
    process.setArguments(QStringList() << "force-changelog");
    process.startDetached();
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    const QString folder = "/temp";
    QString cur = QDir::currentPath();
    QString temp = cur + folder;

    QDir dir;
    if (!dir.exists(temp))
        return 0;

    QDir action;
    QDirIterator it(temp, QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        const QString file = it.next();
        QString newFile = file;
        newFile.remove(folder);

        auto index = newFile.lastIndexOf(R"(/)");
        if (index >= 0)
        {
            QDir dir;
            if (!dir.exists(newFile.mid(0, index)))
                dir.mkpath(newFile.mid(0, index));
        }

        action.remove(newFile);
        action.rename(file, newFile);
    }

    action = QDir(QDir::currentPath() + folder);
    action.removeRecursively();

    return startToolbox();
}
