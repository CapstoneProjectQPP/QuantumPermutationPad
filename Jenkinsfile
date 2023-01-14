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
                parallel(
                    E2E: {
                        dir('test_framework_package') {
                            sh 'sudo chmod a+x robot_automation.sh'
                            catchError {
                                sh 'sudo ./robot_automation.sh'
                            }
                            robot outputPath: '.', logFileName: 'log.html', outputFileName: 'output.xml',
                                                            reportFileName: 'report.hml', passThreshold: 100, unstableThreshold: 75.0, onlyCritical : false

                        }
                    },
                    Unit: {
                        dir('C++') {
                            sh 'make test'
                            archiveArtifacts artifacts: 'bin/unit_test.exe' , fingerprint: true
                        }
                        dir('test_framework_package') {
                            sh 'sudo chmod a+x unit_automation.sh'
                            sh 'sudo ./unit_automation.sh'

                            junit testResults: 'catch_result.xml'
                        }
                    }
                )
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
