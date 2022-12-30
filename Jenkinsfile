pipeline {
    agent any
    stages {
        stage('Build') {
            agent any
            steps {
                dir('C++') {
                  sh 'make'
                  archiveArtifacts artifacts: 'bin/*.exe' , fingerprint: true
                }
            }
        }
        stage('Test') {
            agent any
            steps {
                sh 'sudo chmod -R 777 C++/bin/*'
                dir('test_framework_package') {
                    sh 'sudo chmod a+x test_cpp_binary.sh'
                    sh 'sudo ./test_cpp_binary.sh'
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