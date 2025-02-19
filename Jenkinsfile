pipeline {
    agent any

    environment {
        TELEGRAM_TOKEN = credentials('TELEGRAM_TOKEN')
        TELEGRAM_CHAT_ID = credentials('TELEGRAM_CHAT_ID')
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Build') {
            steps {
                script {
                    try {
                        sh 'g++ -std=c++17 -o hello main.cpp'
                        buildStageStatus = 'Success'
                    } catch (Exception e) {
                        buildStageStatus = 'Failure'
                        throw e
                    }
                }
            }
        }
        stage('Test') {
            steps {
                sh '''
                  set -o pipefail
                  ./hello test | tee results.txt
                '''
            }
        }
        stage('Package Artifacts') {
            steps {
                sh 'zip artifacts.zip hello'
            }
        }
        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: 'artifacts.zip'
            }
        }
    }

    post {
        always {
            script {
                def testResults = fileExists('results.txt') ? readFile('results.txt').trim() : 'No test results available'

                def branchName = env.BRANCH_NAME ?: 'N/A'
                def buildNumber = env.BUILD_NUMBER ?: 'N/A'

                def message = """Jenkins Build
[${branchName}]

Build: ${buildStageStatus}
Testing:
${testResults}"""

                sh """
                  curl -s -X POST "https://api.telegram.org/bot$TELEGRAM_TOKEN/sendMessage" \\
                       -d chat_id="$TELEGRAM_CHAT_ID" \\
                       -d text='$message'
                """
            }
        }
    }
}
