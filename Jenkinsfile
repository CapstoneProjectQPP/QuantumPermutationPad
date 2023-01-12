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

                    catchError {
                        sh 'sudo ./automation.sh'
                    }
                    robot outputPath: '.', logFileName: 'log.html', outputFileName: 'output.xml',
                                                    reportFileName: 'report.hml', passThreshold: 100, unstableThreshold: 75.0, onlyCritical : false

                    junit 'utest/output.xml'
                }
            }
        }
    }
    post {
        // Clean after build
        always {

            step([$class: 'GitHubCommitStatusSetter'])


            cleanWs(cleanWhenNotBuilt: false,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                    [pattern: '.propsfile', type: 'EXCLUDE']])
        }
    }
}
