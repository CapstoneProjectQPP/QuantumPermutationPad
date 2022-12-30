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