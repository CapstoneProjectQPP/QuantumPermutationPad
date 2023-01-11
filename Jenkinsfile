pipeline {
    agent any
    stages {
        stage('Build') {
            agent any
            options { skipDefaultCheckout() }
            steps {
                checkout scm
                dir('C++') {
                  sh 'make clean'
                  sh 'make'
                  archiveArtifacts artifacts: 'bin/*.exe' , fingerprint: true
                }
            }
        }
        stage('Test') {
            agent any
            steps {
                dir('test_framework_package') {
                    sh 'sudo chmod a+x *.sh'
                    sh 'sudo ./test_cpp_binary.sh'

                    sh 'sudo ./automation.sh'
                }
            }
        }
    }
    post {
        // Clean after build
        always {

            step([$class: 'GitHubCommitStatusSetter'])

            robot outputPath: 'test_framework_package/', logFileName: 'log.html', outputFileName: 'output.xml',
                                reportFileName: 'report.hml', passThreshold: 100, unstableThreshold: 75.0

            cleanWs(cleanWhenNotBuilt: false,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                    [pattern: '.propsfile', type: 'EXCLUDE']])
        }
    }
}
