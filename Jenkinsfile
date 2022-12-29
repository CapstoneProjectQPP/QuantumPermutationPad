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

          githubPRStatusPublisher buildMessage: message(failureMsg: githubPRMessage('Can\'t set status; build failed.'), successMsg: githubPRMessage('Can\'t set status; build succeeded.')), errorHandler: statusOnPublisherError('FAILURE'), statusMsg: githubPRMessage('${GITHUB_PR_COND_REF} run ended'), unstableAs: 'FAILURE'

          cleanWs(cleanWhenNotBuilt: false,
                  deleteDirs: true,
                  disableDeferredWipeout: true,
                  notFailBuild: true,
                  patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                             [pattern: '.propsfile', type: 'EXCLUDE']])
      }
  }
}