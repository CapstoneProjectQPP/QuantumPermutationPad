pipeline {
  agent any
  stages {
    stage('Build') {
      agent any
      steps {
        dir('C++') {
            try {
                    sh 'make'
                } catch (err) {
                    echo "Caught: ${err}"
                    currentBuild.result = 'FAILURE'
                }

          archiveArtifacts artifacts: 'bin/*' , fingerprint: true
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