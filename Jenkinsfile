pipeline {
  agent any
  stages {
    stage('Build') {
      agent any
      steps {
        dir('C++') {
          sh 'make'
          archiveArtifacts artifacts: 'bin/*' , fingerprint: true
        }
      }
    }
  }
  post {

      // Clean after build
      always {

            gitHubPRStatus githubPRMessage('${GITHUB_PR_COND_REF} run started')

          cleanWs(cleanWhenNotBuilt: false,
                  deleteDirs: true,
                  disableDeferredWipeout: true,
                  notFailBuild: true,
                  patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                             [pattern: '.propsfile', type: 'EXCLUDE']])
      }
  }
}